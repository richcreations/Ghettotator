/*!
* @file rotator_pins.h
*
* It is a header file for pin mapping.
*
* Licensed under the GPLv3
*
*/

#ifndef ROTATOR_PINS_H_
#define ROTATOR_PINS_H_

// Truglodite: rename to match actual hardware https://osoyoo.com/wp-content/uploads/2017/04/Arduino-CNC-Shield-Scematics-V3.XX_.jpg
//#define M1IN1 10 ///< Motor 1 PWM pin
#define M1IN1 2 // X step
#define M1IN2 5  // X dir
#define M1SF  7  // Z dir (not needed?)
#define M1FB  A1 // GRBL pin2 (not needed?)

#define M2IN1 3 // Y Step
#define M2IN2 6  // Y Dir
#define M2SF  7 // Z dir (not needed?)
#define M2FB  A0 // GRBL pin3 (not needed?)

#define MOTOR_EN 8 // Enable

#define SW1 11 // Z endstop
#define SW2 9 // X endstop

#define RS485_DIR 2 // X Step (defined above!)

#define SDA_PIN 3 // Y step (defined above!
#define SCL_PIN 4 // Z step

#define PIN12 12 // Spindle Enable
#define PIN13 13 // Spindle Direction
#define A2    A2 // GRBL pin3 (not needed?)
#define A3    A3 // Coolant

#endif /* ROTATOR_PINS_H_ */
