// Pins file for Arduino Nano w/ Nano CNC V4 Sheild
// https://www.instructables.com/How-to-Use-the-CNC-V4-Board-despite-Its-quirks/
// https://content.instructables.com/FLX/AQMK/JFIIPA0Q/FLXAQMKJFIIPA0Q.png
// https://content.instructables.com/FBX/XL1D/KRJ7OATR/FBXXL1DKRJ7OATR.png
// https://www.amazon.com/NOYITO-Engraving-Machine-Expansion-Compatible/dp/B07BGVST9D
//
// Note: The Nano CNC V4 sheild was made by folks who don't understand circuit design.
// All all of the driver MSx jumpers are connected to ground instead of Vcc. 
// Therefore hardware hacks are required if microsteps > 1 is used.

#define aziStepPin      5   // X step
#define aziDirPin       2   // X dir
#define aziENpin        8   // Same pin for all drivers
#define eleStepPin      6   // Y Step
#define eleDirPin       3   // Y Dir
#define eleENpin        8   // ...
#define polStepPin      7   // Z Step
#define polDirPin       4   // Z Dir
#define polENpin        8   // ...
// No boards with hardware pullups so far
#define aziMinStopPin   9   // X endstop
#define eleMinStopPin   10  // Y endstop
#define polMinStopPin   11  // Z endstop

// "L" LED on the nano board (shield has no LED's)
#define ledPinBuiltin   13  // Onboard led pin (also broken out to D13 pins, but after the resistor :()
#define ledPinExternal  A0  // External led pin (pin labeled "ABORT")

#define polPotPin       A6  // Polarize manual control potentiometer  wiper (A6 connector)
