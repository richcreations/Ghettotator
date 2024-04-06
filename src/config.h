// USER CONFIGURATION: Edit this file to suit your specific build. 
// Most times this is the only file that needs to be touch.

// Uncomment only one board from the list below... see boards file and /images for more info.
// If using a custom board file, leave all these commented, and use the custom board 
// setting below, and change filename to match your board file (which should be in boards).
// Note some microprocessors may not yet be defined in platform.ini. If there is no build option
// for your board, a section may be added to platform.ini to accomodate.
// When adding a new board, consider adding a schematic to /images for user reference.

//#define UNO_CNC_SHIELD_V_3
#define RAMPS_V_1_4_MEGA2560

//#include <../boards/nameofcustomboard.h> // edit and uncomment for a custom board file.

// Uncomment to enable antenna polarity rotator feature (poti from 0V to Vcc)
#define POLARIZER
//#define POL_POT_HYSTERESIS  5     // Increase to eliminate polarize axis shaking while poti is not moved

// Uncomment to enable parking feature
//#define PARKING

// Uncomment and move debug led to troubled spot
//#define DEBUG                   

// Disable motors if WDT is triggered
#define WATCHDOG                  

// The following lines can be uncommented and values changed to overide default settings (default settings shown for reference)

// #define BAUDRATE           9600  // Set the Baudrate of easycomm 3 protocol (9600)

// #define AZI_RATIO          57    // Azimuth mechanical gear ratio
// #define AZI_MICROSTEP      1     // Azimuth stepper driver microstepping (<=4)
// #define AZI_VMAX           45.0 // Antenna deg/s
// #define AZI_ACC_MAX        120.0 // Antenna deg/s^2
// #define AZI_MIN_ANGLE      0.0   // Minimum antenna azimuth angle
// #define AZI_MAX_ANGLE      360.0 // Maximum antenna azimuth angle
// #define AZI_PARK_ANGLE     90.0  // Antenna azimuth parking position

// #define ELE_RATIO          57    // Elevation mechanical gear ratio
// #define ELE_MICROSTEP      1     // Elevation stepper driver microstepping (<=4)
// #define ELE_VMAX           45.0 // Antenna deg/s
// #define ELE_ACC_MAX        120.0 // Antenna deg/s^2
// #define ELE_MIN_ANGLE      0.0   // Minimum antenna elevation angle
// #define ELE_MAX_ANGLE      180.0 // Maximum antenna elevation angle
// #define ELE_PARK_ANGLE     -5.0  // Antenna elevation parking position

// #define POL_RATIO          3     // Polarization mechanical gear ratio
// #define POL_MICROSTEP      1     // Polarization stepper driver microstepping (<=4)
// #define POL_VMAX           180.0 // Antenna deg/s
// #define POL_ACC_MAX        120.0 // Antenna deg/s^2
// #define POL_MIN_ANGLE      0.0   // Minimum antenna polarization angle
// #define POL_MAX_ANGLE      180.0 // Maximum antenna polarization angle
// #define POL_PARK_ANGLE     0.0   // Antenna polarizer parking position

// #define SPR                200.0 // Motor steps per revolution (200.0 for standard 1.8degree motors)
// #define MIN_PULSE_WIDTH    20    // uSec (for AccelStepper)
// #define DEFAULT_HOME_STATE LOW   // Low for N.O. switches
// #define HOME_DELAY         2000  // millis to keep moving after hitting endstop (time to settle before resetting zeros)


