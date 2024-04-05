// Pins file for the Anet A8 classic 3d printer motherboard (mega1280p w/ 4xA4988's built in)
// https://github.com/ralf-e/ANET-3D-Board-V1.0/blob/master/ANET3D_Board_Schematic.png
// Note: The a8 motherboard has built in driver MSx pullups installed; use "XXX_MICROSTEP = 16" in config.h.
#define eleStep      15  // X step
#define eleDir       21  // X dir
#define eleEN        14  // XY enable
#define aziStep      22  // Y Step
#define aziDir       23  // Y Dir
#define aziEN        14  // XY enable
#define polStep      3   // Z Step
#define polDir       2   // Z Dir
#define polEN        A5  // Z enable
#define tunStep      1   // E Step
#define tunDir       0   // E Dir
// Again, no hardware pullups
#define eleMinStop   18  // X endstop
#define aziMinStop   19  // Y endstop
#define polMinStop   20  // Z endstop

#define ledExists    1   // onboard led
#define ledPin       A4  // onboard led

#define polPotPin    A3  // Polarize manual control potentiometer wiper (pin #3 on LCD connector)
