/*!
 * @file stepper_motor_controller.ino
Satnogs firmware cleaned up and simplified, with a focus on steppers and sensors. 

 ...old doc reference below
 *
 * This is the documentation for satnogs rotator controller firmware
 * for stepper motors configuration. The board (PCB) is placed in
 * <a href="https://gitlab.com/librespacefoundation/satnogs/satnogs-rotator-controller">
 * satnogs-rotator-controller </a> and is for releases:
 * v2.0
 * v2.1
 * v2.2
 * <a href="https://wiki.satnogs.org/SatNOGS_Rotator_Controller"> wiki page </a>
 *
 * @section dependencies Dependencies
 *
 * This firmware depends on <a href="http://www.airspayce.com/mikem/arduino/AccelStepper/index.htmlhttp://www.airspayce.com/mikem/arduino/AccelStepper/index.html">
 * AccelStepper library</a> being present on your system. Please make sure you
 * have installed the latest version before using this firmware.
 *
 * @section license License
 *
 * Licensed under the GPLv3.
 *
 */

#ifdef DEBUG
    bool debug = 1;
#endif

#include <config.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <../lib/globals.h>
#include <../lib/easycomm.h>
#include <../lib/endstop.h>
#ifdef UNO_CNC_SHIELD_V_3
    #include <../pins/unoCncV3.h>
#endif
#ifdef BRUSHES_N_POTS
    #include <../pins/brushesNpots.h>
#endif
#ifdef ANET_A8_ATMEGA1280_PRINTER_BOARD
    #include <../pins/anet_a8_atmega1280.h>
#endif
#ifdef RAMPS_V_1_4_MEGA2560
    #include <../pins/ramps_V_1_4.h>
#endif
#include <../lib/watchdog.h>

uint32_t t_run = 0; // run time of uC
easycomm comm;
// syntax: AccelStepper stepper_x(interface, stepPin, dirPin); 1=AccelStepper::DRIVER aka standard STEP/DIR drivers
AccelStepper stepper_el(1, eleStep, eleDir);
AccelStepper stepper_az(1, aziStep, aziDir);
endstop switch_eleMin(eleMinStop, DEFAULT_HOME_STATE), switch_aziMin(aziMinStop, DEFAULT_HOME_STATE);

#ifdef WATCHDOG
    wdt_timer wdt;
#endif

enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin);

int32_t deg2step(float deg, float ratio, float microsteps);
float step2deg(int32_t step, float ratio, float microsteps);

int32_t eleMaxStepRate = 0;
int32_t eleMaxStepAcc = 0;
int32_t aziMaxStepRate = 0;
int32_t aziMaxStepAcc = 0;

bool ledState = 0;  //logic
uint32_t ledPeriod = 1000; // msec
uint32_t ledTime = 0; //timer

void setup() {
    // Homing switch
    switch_eleMin.init();
    switch_aziMin.init();

    // Serial Communication
    comm.easycomm_init();
    
    // Azimuth motor
    stepper_az.setEnablePin(aziEN);
    // syntax: setPinsInverted(dir, step, enable), true/false
    stepper_az.setPinsInverted(false, false, true);
    stepper_az.enableOutputs();
    aziMaxStepRate = deg2step(AZI_VMAX, AZI_RATIO, AZI_MICROSTEP);
    aziMaxStepAcc = deg2step(AZI_ACC_MAX, AZI_RATIO, AZI_MICROSTEP);
    stepper_az.setMaxSpeed(aziMaxStepRate);
    stepper_az.setAcceleration(aziMaxStepAcc);
    stepper_az.setMinPulseWidth(MIN_PULSE_WIDTH);

    // Elevation motor
    stepper_el.setEnablePin(eleEN);
    stepper_el.setPinsInverted(false, false, true);
    eleMaxStepRate = deg2step(ELE_VMAX, ELE_RATIO, ELE_MICROSTEP);
    eleMaxStepAcc = deg2step(ELE_ACC_MAX, ELE_RATIO, ELE_MICROSTEP);
    stepper_el.enableOutputs();
    stepper_el.setMaxSpeed(eleMaxStepRate);
    stepper_el.setAcceleration(eleMaxStepAcc);
    stepper_el.setMinPulseWidth(MIN_PULSE_WIDTH);

    //  WDT
    #ifdef WATCHDOG
        wdt.watchdog_init();
    #endif
}

void loop() {
    #ifndef DEBUG
        // LED heartbeat: 1hz toggle if loop is alive
        if(ledExists && millis() - ledTime > ledPeriod)   {
            if(ledState)    {
                digitalWrite(ledPin,LOW);
                ledState = 0;
                ledTime = millis();
            }
            else{
                digitalWrite(ledPin,HIGH);
                ledState = 1;
                ledTime = millis();
            }
        }
    #endif

    // Debug LED on... put this where SHTF
    #ifdef DEBUG
        if(ledExists)   {
            digitalWrite(ledPin,HIGH); //turn on led while waiting for motor init
        }
    #endif

    // Update WDT
    #ifdef WATCHDOG
        wdt.watchdog_reset();
    #endif

    // Get end stop status
    rotator.switch_eleMin = switch_eleMin.get_state();
    rotator.switch_aziMin = switch_aziMin.get_state();

    // Run easycomm implementation
    comm.easycomm_proc();

    // Get position of both axis
    control_az.input = step2deg(stepper_az.currentPosition(), AZI_RATIO, AZI_MICROSTEP);
    control_el.input = step2deg(stepper_el.currentPosition(), ELE_RATIO, ELE_MICROSTEP);

    // Check rotator status
    if (rotator.rotator_status != error) {
        if (rotator.homing_flag == false) {
            // Check home flag
            rotator.control_mode = position;
            // Homing
            rotator.rotator_error = homing(deg2step(-MAX_AZI_ANGLE, AZI_RATIO, AZI_MICROSTEP),
                                           deg2step(-MAX_ELE_ANGLE, ELE_RATIO, ELE_MICROSTEP));
            if (rotator.rotator_error == no_error) {
                // No error
                rotator.rotator_status = idle;
                rotator.homing_flag = true;
            } 
            else {
                // Error
                rotator.rotator_status = error;
                rotator.rotator_error = homing_error;
            }
        } 

        else {
            // Control Loop
            stepper_az.moveTo(deg2step(control_az.setpoint, AZI_RATIO, AZI_MICROSTEP));
            stepper_el.moveTo(deg2step(control_el.setpoint, ELE_RATIO, ELE_MICROSTEP));
            rotator.rotator_status = pointing;
            // Move azimuth and elevation motors
            stepper_az.run();
            stepper_el.run();
            // Idle rotator
            if (stepper_az.distanceToGo() == 0 && stepper_el.distanceToGo() == 0) {
                rotator.rotator_status = idle;
            }
        }
    } 
    else {
        // Error handler, stop motors and disable the motor driver
        stepper_az.stop();
        stepper_az.disableOutputs();
        stepper_el.stop();
        stepper_el.disableOutputs();
        if (rotator.rotator_error != homing_error) {
            // Reset error according to error value
            rotator.rotator_error = no_error;
            rotator.rotator_status = idle;
        }
    }
}

/**************************************************************************/
/*!
    @brief    Move both axis with one direction in order to find home position,
              end-stop switches
    @param    seek_aziMin
              Steps to find home position for azimuth axis
    @param    seek_eleMin
              Steps to find home position for elevation axis
    @return   _rotator_error
*/
/**************************************************************************/
enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin) {
    bool isHome_az = false;
    bool isHome_el = false;

    // Move motors to "seek" position
    stepper_az.moveTo(seek_aziMin);
    stepper_el.moveTo(seek_eleMin);

    // Homing loop
    while (isHome_az == false || isHome_el == false) {
        // Update WDT
       // wdt.watchdog_reset();
        if (switch_aziMin.get_state() == true && !isHome_az) {
            // Found azimuth home
            stepper_az.moveTo(stepper_az.currentPosition());
            isHome_az = true;
        }
        if (switch_eleMin.get_state() == true && !isHome_el) {
            // Found elevation home
            stepper_el.moveTo(stepper_el.currentPosition());
            isHome_el = true;

        }
        // Check if the rotator goes out of limits or something goes wrong (in
        // mechanical)
        if ((stepper_az.distanceToGo() == 0 && !isHome_az) ||
            (stepper_el.distanceToGo() == 0 && !isHome_el)){
            return homing_error;
        }
        // Move motors
        stepper_az.run();
        stepper_el.run();
    }


    // Delay to Deccelerate and homing, to complete the movements
    uint32_t time = millis();
    while (millis() - time < HOME_DELAY) {
       // wdt.watchdog_reset();
        stepper_az.run();
        stepper_el.run();
    }
    // Set the home position and reset all critical control variables
    stepper_az.setCurrentPosition(0);
    stepper_el.setCurrentPosition(0);
    control_az.setpoint = 0;
    control_el.setpoint = 0;

    return no_error;
}

/**************************************************************************/
/*!
    @brief    Convert degrees to steps according to step/revolution, rotator
              gear box ratio and microsteps
    @param    deg
              Degrees in float format
    @return   Steps for stepper motor driver, int32_t
*/
/**************************************************************************/
int32_t deg2step(float deg, float ratio, float microsteps) {
    return (ratio * SPR * microsteps * deg / 360);
}

/**************************************************************************/
/*!
    @brief    Convert steps to degrees according to step/revolution, rotator
              gear box ratio and microsteps
    @param    step
              Steps in int32_t format
    @return   Degrees in float format
*/
/**************************************************************************/
float step2deg(int32_t step, float ratio, float microsteps) {
    return (360.00 * step / (SPR * ratio * microsteps));
}