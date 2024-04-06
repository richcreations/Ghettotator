// Pins file for the Uno CNC Shield V3
// https://europe1.discourse-cdn.com/arduino/original/4X/3/5/f/35f56e460a19e6a426e59053e5a4753201b918a8.png
#define aziStepPin      2   // X step
#define aziDirPin       5   // X dir
#define aziENpin        8   // Same pin for all drivers
#define eleStepPin      3   // Y Step
#define eleDirPin       6   // Y Dir
#define eleENpin        8   // ...
#define polStepPin      4   // Z Step
#define polDirPin       7   // Z Dir
#define polENpin        8   // ...
#define tunStepPin      12  // A Step (remove spindle en jumper)
#define tunDirPin       13  // A Dir (remove spindle dir jumper)
#define tunENpin        8   // ...
// No boards with hardware pullups so far
#define aziMinStopPin   9   // X endstop
#define eleMinStopPin   10  // Y endstop
#define polMinStopPin   11  // Z endstop

// sheild has no built in led...
//#define ledExists         // Onboard led, uncomment to enable
#define ledPin          0   // Onboard led pin

#define polPotPin       A0  // Polarize manual control potentiometer  wiper (GRBL interface pin3)
