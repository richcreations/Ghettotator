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
#define M1IN1 2 ///< Motor 1 PWM pin; from sheild schem - X step
#define M1IN2 5  ///< Motor 1 PWM pin; from sheild schem - X dir
#define M1SF  7  ///< Motor 1 digital input, status flag for DC Motor Drivers; from sheild schem - Z dir (not needed?)
#define M1FB  A1 ///< Motor 1 analog input, current/load feedback for DC Motor Drivers; from sheild schem - GRBL pin2 (not needed?)

#define M2IN1 3 ///< Motor 2 PWM pin; from sheild schem - Y Step
#define M2IN2 6  ///< Motor 2 PWM pin; from sheild schem - Y Dir
#define M2SF  7 ///< Motor 2 digital input, status flag for DC Motor Drivers; from sheild schem - Z dir (not needed?)
#define M2FB  A0 ///< Motor 2 analog input, current/load feedback for DC Motor Drivers; from sheild schem - GRBL pin3 (not needed?)

#define MOTOR_EN 8 ///< Digital output, to enable the motors; from sheild schem - Enable

#define SW1 11 ///< Digital input, to read the status of end-stop for motor 1; from sheild schem - Z endstop
#define SW2 9 ///< Digital input, to read the status of end-stop for motor 2; from sheild schem - X endstop

#define RS485_DIR 2 ///< Digital output, to set the direction of RS485 communication; from sheild schem - X Step (second appearance!)

#define SDA_PIN 3 ///< I2C data pin; from sheild schem - Y step (second appearance!
#define SCL_PIN 4 ///< I2C clock pin; from sheild schem - Z step

#define PIN12 12 ///< General purpose I/O pin; from sheild schem - Spindle Enable
#define PIN13 13 ///< General purpose I/O pin; from sheild schem - Spindle Direction
#define A2    A2 ///< General purpose I/O & analog pin; from sheild schem - GRBL pin3 (not needed?)
#define A3    A3 ///< General purpose I/O & analog pin; from sheild schem - Coolant

#endif /* ROTATOR_PINS_H_ */
