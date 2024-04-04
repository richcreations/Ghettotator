// USER CONFIGURATION

// Uncomment one board from the list... or add a pins file if needed.
//#define UNO_CNC_SHIELD_V_3
#define ANET_A8_ATMEGA1280_PRINTER_BOARD
//#define RAMPS_V_1_4_MEGA2560

#define BAUDRATE           9600  // Set the Baudrate of easycomm 3 protocol (9600)

#define AZI_RATIO          108.0 // Azimuth mechanical gear ratio
#define AZI_MICROSTEP      16.0  // Azimuth driver microsteps
#define AZI_VMAX           300   // Antenna deg/s
#define AZI_ACC_MAX        120   // Antenna deg/s^2
#define AZI_MIN_ANGLE      0     // Minimum angle of azimuth
#define AZI_MAX_ANGLE      360   // Maximum angle of azimuth

#define ELE_RATIO          108.0 // Elevation mechanical gear ratio
#define ELE_MICROSTEP      16.0  // Elevation driver microsteps
#define ELE_VMAX           300   // Antenna deg/s
#define ELE_ACC_MAX        120   // Antenna deg/s^2
#define ELE_MIN_ANGLE      0     // Minimum angle of elevation
#define ELE_MAX_ANGLE      180   // Maximum angle of elevation

#define SPR                200.0 // Motor steps per revolution (200.0 for standard 1.8degree motors)
#define MIN_PULSE_WIDTH    20    // uSec (for AccelStepper)
#define DEFAULT_HOME_STATE LOW   // Change to LOW according to Home sensor
#define HOME_DELAY         50   // millis to keep moving after hitting endstop??! WTF lol
#define SAMPLE_TIME        0.1   // Control loop in sec

#define WATCHDOG                 // Disable motors if WDT is triggered
//#define DEBUG                  // Uncomment and move debug led to troubled spot 