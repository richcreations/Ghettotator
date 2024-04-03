/*!
 * @file stepper_motor_controller.ino
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

uint32_t t_run = 0; // run time of uC
easycomm comm;
AccelStepper stepper_az(1, aziStep, aziDir);
AccelStepper stepper_el(1, eleStep, eleDir);
endstop switch_eleMin(eleMinStop, DEFAULT_HOME_STATE), switch_aziMin(aziMinStop, DEFAULT_HOME_STATE);
//wdt_timer wdt;

enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin);
int32_t deg2step(float deg);
float step2deg(int32_t step);
int32_t eleMaxStepRate = 0;
int32_t eleMaxStepAcc = 0;
int32_t aziMaxStepRate = 0;
int32_t aziMaxStepAcc = 0;

void setup() {
    // Homing switch
    switch_eleMin.init();
    switch_aziMin.init();

    // Serial Communication
    comm.easycomm_init();

    // Stepper Motor setup
    stepper_az.setEnablePin(aziEN);
    stepper_az.setPinsInverted(false, false, true);
    stepper_az.enableOutputs();
    eleMaxStepRate = deg2step(ELE_VMAX);
    eleMaxStepAcc = deg2step(ELE_ACC_MAX);
    stepper_az.setMaxSpeed(eleMaxStepRate);
    stepper_az.setAcceleration(eleMaxStepAcc);
    stepper_az.setMinPulseWidth(MIN_PULSE_WIDTH);
    stepper_az.setEnablePin(eleEN);
    stepper_el.setPinsInverted(false, false, true);
    stepper_el.enableOutputs();
    aziMaxStepRate = deg2step(AZI_VMAX);
    stepper_el.setMaxSpeed(aziMaxStepRate);
    aziMaxStepAcc = deg2step(AZI_ACC_MAX);
    stepper_el.setAcceleration(aziMaxStepAcc);
    stepper_el.setMinPulseWidth(MIN_PULSE_WIDTH);

    // Initialize WDT
   // wdt.watchdog_init();
}

void loop() {
    // Update WDT
   // wdt.watchdog_reset();

    // Get end stop status
    rotator.switch_eleMin = switch_eleMin.get_state();
    rotator.switch_aziMin = switch_aziMin.get_state();

    // Run easycomm implementation
    comm.easycomm_proc();

    // Get position of both axis
    control_az.input = step2deg(stepper_az.currentPosition());
    control_el.input = step2deg(stepper_el.currentPosition());

    // Check rotator status
    if (rotator.rotator_status != error) {
        if (rotator.homing_flag == false) {
            // Check home flag
            rotator.control_mode = position;
            // Homing
            rotator.rotator_error = homing(deg2step(-MAX_AZI_ANGLE),
                                           deg2step(-MAX_ELE_ANGLE));
            if (rotator.rotator_error == no_error) {
                // No error
                rotator.rotator_status = idle;
                rotator.homing_flag = true;
            } else {
                // Error
                rotator.rotator_status = error;
                rotator.rotator_error = homing_error;
            }
        } else {
            // Control Loop
            stepper_az.moveTo(deg2step(control_az.setpoint));
            stepper_el.moveTo(deg2step(control_el.setpoint));
            rotator.rotator_status = pointing;
            // Move azimuth and elevation motors
            stepper_az.run();
            stepper_el.run();
            // Idle rotator
            if (stepper_az.distanceToGo() == 0 && stepper_el.distanceToGo() == 0) {
                rotator.rotator_status = idle;
            }
        }
    } else {
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
        if (switch_eleMin.get_state() == true && !isHome_az) {
            // Find azimuth home
            stepper_az.moveTo(stepper_az.currentPosition());
            isHome_az = true;
        }
        if (switch_aziMin.get_state() == true && !isHome_el) {
            // Find elevation home
            stepper_el.moveTo(stepper_el.currentPosition());
            isHome_el = true;
        }
        // Check if the rotator goes out of limits or something goes wrong (in
        // mechanical)
        if ((stepper_az.distanceToGo() == 0 && !isHome_az) ||
            (stepper_el.distanceToGo() == 0 && !isHome_el)){
            return homing_error;
        }
        // Move motors to "seek" position
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
              gear box ratio and microstep
    @param    deg
              Degrees in float format
    @return   Steps for stepper motor driver, int32_t
*/
/**************************************************************************/
int32_t deg2step(float deg) {
    return (RATIO * SPR * MICROSTEP * deg / 360);
}

/**************************************************************************/
/*!
    @brief    Convert steps to degrees according to step/revolution, rotator
              gear box ratio and microstep
    @param    step
              Steps in int32_t format
    @return   Degrees in float format
*/
/**************************************************************************/
float step2deg(int32_t step) {
    return (360.00 * step / (SPR * RATIO * MICROSTEP));
}