// Pins file for the Anet A8 classic 3d printer motherboard (mega1280p w/ 4xA4988's built in)
// https://github.com/ralf-e/ANET-3D-Board-V1.0/blob/master/ANET3D_Board_Schematic.png
// This board has built in driver MSx pullups; you must use "XXX_MICROSTEP = 16" in config.h.
#define aziStepPin      15  // X step
#define aziDirPin       21  // X dir
#define aziENpin        14  // XY enable
#define eleStepPin      22  // Y Step
#define eleDirPin       23  // Y Dir
#define eleENpin        14  // XY enable
#define polStepPin      3   // Z Step
#define polDirPin       2   // Z Dir
#define polENpin        A5  // Z enable
#define tunStepPin      1   // E Step
#define tunDirPin       0   // E Dir
// Again, no hardware pullups
#define eleMinStopPin   18  // X endstop
#define aziMinStopPin   19  // Y endstop
#define polMinStopPin   20  // Z endstop

#define ledExists           // Onboard led, uncomment to enable
#define ledPin          A4  // Onboard led

#define polPotPin       A7  // Polarize manual control potentiometer wiper (E0 temp)
