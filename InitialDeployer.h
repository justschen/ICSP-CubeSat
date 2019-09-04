#ifndef __INITIAL_DEPLOYER__
#define __INITIAL_DEPLOYER__
#include <syslog.h>
#include "Thread.h"
#include "DsaController.h"
#include "InitialDsaDeployOp.h"
namespace IrvCS
{
  /**
   * Run initial deployment in a thread.  Initial deployment occurs 
   * when the satellite powers on for the first time after launch.
   * 
   **/
  class InitialDeployer:public Thread
  {
  public:
    /**
     * @param controller The DSA Controller object which should never be NULL
     * @param initDeployFile The marker file to indicate that initial deployment
     *        has taken place.
     **/
    InitialDeployer(DsaController *controller, const std::string &initDeployFile)
      :Thread(Thread::Detached), controller_(controller)
      {
        // Create the deploy file
        std::ofstream ofs(initDeployFile.c_str(), std::ios::out);
        ofs<<"1";
        if (ofs.fail())
        {
          syslog(LOG_ERR, "Unable to create %s:  %s (%d)", initDeployFile.c_str(),
                 strerror(errno), errno);
        } else
        {
          syslog(LOG_INFO, 
                 "Created %s to mark initial deployment completion state",
                 initDeployFile.c_str());
        }
      }

    virtual ~InitialDeployer()
      {
      }

    void *run()
      {
        syslog(LOG_INFO, "Performing Initial Deployment Operation");
        IrvCS::InitialDsaDeployOp deployOp(controller_);

        OpStatus status=deployOp.execute();

        if ( StatOk == status )
        {
          syslog(LOG_INFO, "DSA Release/Deploy Operation Successful");
        } else if (StatTimeOut == status)
        {
          syslog(LOG_WARNING, "DSA Release/Deploy Operation Did not complete");
        } else
        {
          syslog(LOG_ERR, "DSA Release/Deploy Operation Errored with status %d", status);
        }
          
        // Done with execution, clean up!
        delete this;
        return NULL;
      }

  private:
    DsaController *controller_;
  };
}
#endif
