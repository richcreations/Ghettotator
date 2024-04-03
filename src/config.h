// USER CONFIGURATION


// Pick one board from the list... or add a pins file if needed.
//#define UNO_CNC_SHIELD_V_3      
//#define BRUSHES_N_POTS
//#define ANET_A8_ATMEGA1280_PRINTER_BOARD
#define RAMPS_V_1_4_MEGA2560

#define SAMPLE_TIME        0.1   // Control loop in s
#define RATIO              108L  // Gear ratio of rotator gear box, default 54
#define MICROSTEP          16L   // Set Microsteps
#define MIN_PULSE_WIDTH    20    // In microsecond for AccelStepper
#define AZI_VMAX           90    // In deg/s
#define ELE_VMAX           90    // In deg/s
#define AZI_ACC_MAX        120   // In deg/s^2
#define ELE_ACC_MAX        120   // In deg/s^2
#define SPR                200L  // Step Per Revolution
#define MIN_AZI_ANGLE      0     // Minimum angle of azimuth
#define MAX_AZI_ANGLE      360   // Maximum angle of azimuth
#define MIN_ELE_ANGLE      0     // Minimum angle of elevation
#define MAX_ELE_ANGLE      180   // Maximum angle of elevation
#define DEFAULT_HOME_STATE LOW   // Change to LOW according to Home sensor
#define HOME_DELAY         12000 // Time for homing Deceleration in millisecond