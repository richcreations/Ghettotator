// USER CONFIGURATION


// Pick one board from the list... or add a pins file if needed.
//#define UNO_CNC_SHIELD_V_3      
//#define BRUSHES_N_POTS
#define ANET_A8_ATMEGA1280_PRINTER_BOARD
//#define RAMPS_V_1_4_MEGA2560

#define SAMPLE_TIME        0.1   // Control loop in sec
#define AZI_RATIO          108L  // Azimuth gear ratio
#define ELE_RATIO          108L  // Elevation gear ratio
#define AZI_MICROSTEP      16L   // Azimuth driver microsteps
#define ELE_MICROSTEP      16L   // Elevation driver microsteps
#define MIN_PULSE_WIDTH    20    // uSec (for AccelStepper)
#define AZI_VMAX           90    // deg/s
#define ELE_VMAX           90    // deg/s
#define AZI_ACC_MAX        120   // deg/s^2
#define ELE_ACC_MAX        120   // deg/s^2
#define SPR                200L  // Step Per Revolution (200 for standard 1.8degree motors)
#define MIN_AZI_ANGLE      0     // Minimum angle of azimuth
#define MAX_AZI_ANGLE      360   // Maximum angle of azimuth
#define MIN_ELE_ANGLE      0     // Minimum angle of elevation
#define MAX_ELE_ANGLE      180   // Maximum angle of elevation
#define DEFAULT_HOME_STATE LOW   // Change to LOW according to Home sensor
#define HOME_DELAY         12000 // Time for homing Deceleration in millisecond