// Pins file for Arduino Nano w/ Nano CNC V4 Sheild
// https://www.instructables.com/How-to-Use-the-CNC-V4-Board-despite-Its-quirks/
// https://content.instructables.com/FLX/AQMK/JFIIPA0Q/FLXAQMKJFIIPA0Q.png
// https://content.instructables.com/FBX/XL1D/KRJ7OATR/FBXXL1DKRJ7OATR.png
// https://www.amazon.com/NOYITO-Engraving-Machine-Expansion-Compatible/dp/B07BGVST9D

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
#define ledExists           // Onboard led, uncomment to enable
#define ledPin          13  // Onboard led pin (on the nano itself, also on D13 shield pin)

#define polPotPin       A6  // Polarize manual control potentiometer  wiper (A6 connector)
