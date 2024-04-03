// Truglodite: rename to match actual hardware https://osoyoo.com/wp-content/uploads/2017/04/Arduino-CNC-Shield-Scematics-V3.XX_.jpg
//#define aziStep 10 ///< Motor 1 PWM pin
#define aziStep      2   // X step
#define aziDir       5   // X dir
#define polDir       7   // Z dir (not needed?)
#define M1FB       A1  // GRBL pin2 (not needed?)

#define eleStep      3   // Y Step
#define eleDir       6   // Y Dir
#define polDir       7   // Z dir (not needed?)
#define M2FB       A0  // GRBL pin3 (not needed?)

#define ENABLE     8   // Enable

#define eleMinStop   11  // Y endstop
#define aziMinStop   9   // X endstop

#define RS485_DIR  2   // X Step (defined above!)

#define SDA_PIN    3   // Y step (defined above!
#define SCL_PIN    4   // Z step

#define PIN12      12  // Spindle Enable
#define PIN13      13  // Spindle Direction
#define A2         A2  // GRBL pin3 (not needed?)
#define A3         A3  // Coolant
