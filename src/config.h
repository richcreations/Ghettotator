// USER CONFIGURATION


// Pick one board from the list... or add a pins file if needed.
#define UNO_CNC_SHIELD_V_3      
//#define BRUSHES_N_POTS
//#define ANET_A8_M1280_PRINTER_BOARD

#define SAMPLE_TIME        0.1   // Control loop in s
#define RATIO              108   // Gear ratio of rotator gear box, default 54
#define MICROSTEP          8     // Set Microstep
#define MIN_PULSE_WIDTH    20    // In microsecond for AccelStepper
#define MAX_SPEED          3200  // In steps/s, consider the microstep
#define MAX_ACCELERATION   1600  // In steps/s^2, consider the microstep
#define SPR                1600L // Step Per Revolution, consider the microstep
#define MIN_M1_ANGLE       0     // Minimum angle of azimuth
#define MAX_M1_ANGLE       360   // Maximum angle of azimuth
#define MIN_M2_ANGLE       0     // Minimum angle of elevation
#define MAX_M2_ANGLE       180   // Maximum angle of elevation
#define DEFAULT_HOME_STATE LOW   // Change to LOW according to Home sensor
#define HOME_DELAY         12000 // Time for homing Deceleration in millisecond