
#include <../src/config.h>


#ifdef DEBUG
    bool debug = 1;
#endif

#ifdef UNO_CNC_SHIELD_V_3
    #include <../boards/unoCncV3.h>
#endif
#ifdef BRUSHES_N_POTS
    #include <../boards/brushesNpots.h>
#endif
#ifdef ANET_A8_ATMEGA1280_PRINTER_BOARD
    #include <../boards/anet_a8_atmega1280.h>
#endif
#ifdef RAMPS_V_1_4_MEGA2560
    #include <../boards/ramps_V_1_4.h>
#endif


#ifndef BAUDRATE
    #define BAUDRATE           9600  // Set the Baudrate of easycomm 3 protocol (9600)
#endif
#ifndef AZI_RATIO
    #define AZI_RATIO          57.0  // Azimuth mechanical gear ratio
#endif
#ifndef AZI_MICROSTEP
    #define AZI_MICROSTEP      16.0  // Azimuth stepper driver microstepping
#endif
#ifndef AZI_VMAX
    #define AZI_VMAX           300   // Antenna deg/s
#endif
#ifndef AZI_ACC_MAX
    #define AZI_ACC_MAX        120   // Antenna deg/s^2
#endif
#ifndef AZI_MIN_ANGLE
    #define AZI_MIN_ANGLE      0     // Minimum antenna azimuth angle
#endif
#ifndef AZI_MAX_ANGLE
    #define AZI_MAX_ANGLE      360   // Maximum antenna azimuth angle
#endif


#ifndef ELE_RATIO
    #define ELE_RATIO          57.0  // Elevation mechanical gear ratio
#endif
#ifndef ELE_MICROSTEP
    #define ELE_MICROSTEP      16.0  // Elevation stepper driver microstepping
#endif
#ifndef ELE_VMAX
    #define ELE_VMAX           300   // Antenna deg/s
#endif
#ifndef ELE_ACC_MAX
    #define ELE_ACC_MAX        120   // Antenna deg/s^2
#endif
#ifndef ELE_MIN_ANGLE
    #define ELE_MIN_ANGLE      0     // Minimum antenna elevation angle
#endif
#ifndef ELE_MAX_ANGLE
    #define ELE_MAX_ANGLE      180   // Maximum antenna elevation angle
#endif

#ifndef POL_RATIO
    #define POL_RATIO          57.0  // Polarization mechanical gear ratio
#endif
#ifndef POL_MICROSTEP
#   define POL_MICROSTEP      16.0  // Polarization stepper driver microstepping (built in MSx pull ups)
#endif
#ifndef POL_VMAX
    #define POL_VMAX           300   // Antenna deg/s
#endif
#ifndef POL_ACC_MAX
    #define POL_ACC_MAX        120   // Antenna deg/s^2
#endif
#ifndef POL_MIN_ANGLE
    #define POL_MIN_ANGLE      0     // Minimum antenna polarization angle
#endif
#ifndef POL_MAX_ANGLE
    #define POL_MAX_ANGLE      180.0 // Maximum antenna polarization angle
#endif

#ifndef SPR
    #define SPR                200.0 // Motor steps per revolution (200.0 for standard 1.8degree motors)
#endif
#ifndef MIN_PULSE_WIDTH
    #define MIN_PULSE_WIDTH    20    // uSec (for AccelStepper)
#endif
#ifndef DEFAULT_HOME_STATE LOW
    #define DEFAULT_HOME_STATE LOW   // Low for N.O. switches and pullups
#endif
#ifndef HOME_DELAY
    #define HOME_DELAY         0     // millis to keep moving after hitting endstop
#endif
#ifndef SAMPLE_TIME
    #define SAMPLE_TIME        0.1   // Control loop in sec
#endif