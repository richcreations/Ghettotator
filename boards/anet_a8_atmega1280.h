// Pins file for the Anet A8 classic 3d printer motherboard (mega1280p w/ 4xA4988's built in)
// https://github.com/ralf-e/ANET-3D-Board-V1.0/blob/master/ANET3D_Board_Schematic.png
// Note: The a8 motherboard has built in driver MSx pullups installed; use "XXX_MICROSTEP = 16" in config.h.
#define eleStepPin      15  // X step
#define eleDirPin       21  // X dir
#define eleENpin        14  // XY enable
#define aziStepPin      22  // Y Step
#define aziDirPin       23  // Y Dir
#define aziENpin        14  // XY enable
#define polStepPin      3   // Z Step
#define polDirPin       2   // Z Dir
#define polENpin        A5  // Z enable
#define tunStepPin      1   // E Step
#define tunDirPin       0   // E Dir
// Again, no hardware pullups
#define eleMinStopPin   18  // X endstop
#define aziMinStopPin   19  // Y endstop
#define polMinStopPin   20  // Z endstop

#define ledExists       1   // Onboard led
#define ledPin          A4  // Onboard led

#define polPotPin       A3  // Polarize manual control potentiometer wiper (pin #3 on LCD connector)
