// Pins file for the Uno CNC Shield V3
// https://europe1.discourse-cdn.com/arduino/original/4X/3/5/f/35f56e460a19e6a426e59053e5a4753201b918a8.png
#define eleStep      2   // X step
#define eleDir       5   // X dir
#define eleEN        8   // Same pin for all drivers
#define aziStep      3   // Y Step
#define aziDir       6   // Y Dir
#define aziEN        8   // ...
#define polStep      4   // Z Step
#define polDir       7   // Z Dir
#define polEN        8   // ...
#define tunStep      12  // A Step (remove spindle en jumper)
#define tunDir       13  // A Dir (remove spindle dir jumper)
#define tunEN        8   // ...
// No boards with hardware pullups so far
#define aziMinStop   9   // X endstop
#define eleMinStop   10  // Y endstop
#define polMinStop   11  // Z endstop

// sheild has no built in led...
#define ledExists    0  // onboard led
#define ledPin       0  // onboard led

#define polPotPin    A0 // Polarize manual control potentiometer  wiper (GRBL interface pin3)
