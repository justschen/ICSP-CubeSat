#ifndef __CCARD_DEFS_H__
#define __CCARD_DEFS_H__
namespace IrvCS
{
/// If no operations in 5 minutes, switch to idle mode **/
#define C_CARD_IDLE_THRESHOLD 5*60 

/// how often to check for idle
#define C_CARD_IDLE_CHECK_INTERVAL 60

#define MSG_TYPE_OFFSET_BITS 16
#define MSG_ID_OFFSET_BITS 0
#define MSG_CMD_OFFSET_BITS 8

#define DSA1_RELEASE_STATUS_BIT 0
#define DSA1_DEPLOY_STATUS_BIT  1
#define DSA2_RELEASE_STATUS_BIT 2
#define DSA2_DEPLOY_STATUS_BIT  3

/**
 * Initial Deploy Delay in seconds.  How long to wait to initiate the initial deployment
 * sequence.  30 minutes default.  Should deploy before antennae to avoid possible 
 * antennae obstruction.
 * May be overridden using the DEBUG_DEPLOY_DELAY_FILE
 * for testing
 **/
#define INITIAL_DEPLOY_DELAY 30*60

/**
 * Deploy delay debug override flag.  For testing the following file should contain
 * the deploy delay in seconds.  Prior to launch this will be cleaned.
 **/
#define DEBUG_DEPLOY_DELAY_FILE "/data/debug/deployDelay"

/**
 * Idle Mode disable - create this file if you don't want idle mode
 **/
#define IDLE_MODE_DISABLE_FILE "/data/debug/idleDisable"
  
/**
 * Timeout for each release operation in seconds.
 * NOTE:  Watchdog kills processes after 45 seconds.
 **/  
#define DSA_RELEASE_TIMEOUT 15

/**
 * Wait in seconds between Release retries
 **/
#define DSA_RELEASE_WAIT 5

/**
 * Wait in seconds in between operations.  
 * This wasn't specified in Cmdr Nader's algorithm, so make this minimal
 **/
#define DSA_OP_WAIT 1
  
/**
 * Timeout for Deploy operation in seconds
 **/
#define DSA_DEPLOY_TIMEOUT 10

/**
 * Additional attempt to release
 **/
#define DSA_EMERGENCY_RELEASE_TIMEOUT 15

/**
 * Client timeout padding to wait for response from server (seconds)
 **/
#define TIMEOUT_PADDING 3

  /**
   * Operation Status Codes.  Value <0 indicates an error status
   **/
  enum OpStatus
  {
    StatTimeOut=-10,
    StatDeviceAccess=-3,        /* Problems accessing the device */
    StatInvalidInput=-2,        /* Invalid function parameters */
    StatErr=-1,                 /* General error */
    StatOk=0,                   /* Successful operation */
    StatOpInProgress=1,         /* Operation in progress */
  };
  
  enum MsgTypes
  {
    MsgDsa=0,
    MsgMt=1,
    MaxTypes
  };
  
  /**
   * DSA commands to release and deploy
   */
  enum DsaCmd
  {
    Release=0,     
    Deploy=1,
    Reset=2,  // reset DSA to initial value (1)
    CmdUnknown
  };

  /**
   * DSA 1 and DSA 2 ID's.  Values are chosen for encoding/decoding efficiency
   * when writing to the i2c output register.  Only one should be set at a given
   * time
   * 
   * Used as the shift offset.
   */
  enum DsaId
  {
    DSA_1=0,
    DSA_2=2,
    DSA_UNKNOWN
  };

  /**
   * Magnetorquer state bit is 0 for on and 1 for off
   **/
  enum MtState
  {
    Off=0,
    On=1
  };

  /**
   * Magnetorquer ID is the first 3 bits representing x, y, and z
   * respectively.  Multiple bits may be set at a given time
   **/
  enum MtId
  {
    MT_1=1,
    MT_2=2,
    MT_3=4
  };

  enum CCardError
  {
    CC_OK=0,
    CC_Timeout=-122
  };
}
#endif  
