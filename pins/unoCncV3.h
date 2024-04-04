// Truglodite: rename to match CNC v3 shield https://osoyoo.com/wp-content/uploads/2017/04/Arduino-CNC-Shield-Scematics-V3.XX_.jpg
#define eleStep      2   // X step
#define eleDir       5   // X dir
#define eleEN        8   // One pin used for all steppers
#define aziStep      3   // Y Step
#define aziDir       6   // Y Dir
#define aziEN        8   // One pin used for all steppers
#define polStep      4   // Z Step
#define polDir       7   // Z Dir
#define polEN        8   // One pin used for all steppers
#define tunStep      12  // A Step (open spindle en jumper)
#define tunDir       13  // A Dir (open spindle dir jumper)
#define tunEN        8   // One pin used for all steppers
// No boards with hardware pullups so far
#define aziMinStop   9   // X endstop
#define eleMinStop   10  // Y endstop
#define eleMinStop   11  // Z endstop

// sheild has no built in led... fake it
#define ledExists    0  // onboard led
#define ledPin       0  // onboard led
