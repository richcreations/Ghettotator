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


#include <defaults.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <../lib/globals.h>
#include <../lib/easycomm.h>
#include <../lib/endstop.h>

#include <../lib/watchdog.h>

uint32_t t_run = 0; // run time of uC
easycomm comm;

// syntax: AccelStepper stepper_x(interface, stepPin, dirPin); 1=AccelStepper::DRIVER aka standard STEP/DIR drivers
AccelStepper stepper_el(1, eleStepPin, eleDirPin);
AccelStepper stepper_az(1, aziStepPin, aziDirPin);

endstop switch_eleMin(eleMinStopPin, DEFAULT_HOME_STATE), switch_aziMin(aziMinStopPin, DEFAULT_HOME_STATE);
#ifdef POLARIZER
    AccelStepper stepper_po(1, polStepPin, polDirPin);
    endstop switch_polMin(polMinStopPin, DEFAULT_HOME_STATE);
#endif

#ifdef WATCHDOG
    wdt_timer wdt;
#endif

#ifndef POLARIZER
    enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin);
#else
    enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin, int32_t seek_polMin);
#endif

int32_t deg2step(float deg, float ratio, float microsteps);
float step2deg(int32_t step, float ratio, float microsteps);

int32_t eleMaxStepRate = 0;
int32_t eleMaxStepAcc = 0;
int32_t aziMaxStepRate = 0;
int32_t aziMaxStepAcc = 0;
#ifdef POLARIZER
    int32_t polMaxStepRate = 0;
    int32_t polMaxStepAcc = 0;
    float polPot = 0;
#endif

bool ledState = 0;  //logic
uint32_t ledPeriod = 1000; // msec
uint32_t ledTime = 0; //timer

void setup() {
    // Initialize homing switches
    switch_eleMin.init();
    switch_aziMin.init();
    #ifdef POLARIZER
        switch_polMin.init();
        pinMode(polPotPin, INPUT); // init poti pin, no pullup
    #endif

    // Serial Communication
    comm.easycomm_init();
    
    // Azimuth motor
    stepper_az.setEnablePin(aziENpin);
    // syntax: setPinsInverted(dir, step, enable), true/false
    stepper_az.setPinsInverted(false, false, true);
    stepper_az.enableOutputs();
    aziMaxStepRate = deg2step(AZI_VMAX, AZI_RATIO, AZI_MICROSTEP);
    aziMaxStepAcc = deg2step(AZI_ACC_MAX, AZI_RATIO, AZI_MICROSTEP);
    stepper_az.setMaxSpeed(aziMaxStepRate);
    stepper_az.setAcceleration(aziMaxStepAcc);
    stepper_az.setMinPulseWidth(MIN_PULSE_WIDTH);

    // Elevation motor
    stepper_el.setEnablePin(eleENpin);
    stepper_el.setPinsInverted(false, false, true);
    eleMaxStepRate = deg2step(ELE_VMAX, ELE_RATIO, ELE_MICROSTEP);
    eleMaxStepAcc = deg2step(ELE_ACC_MAX, ELE_RATIO, ELE_MICROSTEP);
    stepper_el.enableOutputs();
    stepper_el.setMaxSpeed(eleMaxStepRate);
    stepper_el.setAcceleration(eleMaxStepAcc);
    stepper_el.setMinPulseWidth(MIN_PULSE_WIDTH);

    #ifdef POLARIZER        
        // Polarizer motor
        stepper_po.setEnablePin(polENpin);
        stepper_po.setPinsInverted(false, false, true);
        polMaxStepRate = deg2step(POL_VMAX, POL_RATIO, POL_MICROSTEP);
        polMaxStepAcc = deg2step(POL_ACC_MAX, POL_RATIO, POL_MICROSTEP);
        stepper_po.enableOutputs();
        stepper_po.setMaxSpeed(polMaxStepRate);
        stepper_po.setAcceleration(polMaxStepAcc);
        stepper_po.setMinPulseWidth(MIN_PULSE_WIDTH);
    #endif

    //  WDT
    #ifdef WATCHDOG
        wdt.watchdog_init();
    #endif
}

void loop() {
    #ifndef DEBUG
        // LED heartbeat: slow blink when loop is running
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
    #ifdef POLARIZER
        rotator.switch_polMin = switch_polMin.get_state();
        polPot = float(analogRead(polPotPin));
    #endif

    // Run easycomm implementation
    comm.easycomm_proc();

    // Get position of axis
    control_az.input = step2deg(stepper_az.currentPosition(), AZI_RATIO, AZI_MICROSTEP);
    control_el.input = step2deg(stepper_el.currentPosition(), ELE_RATIO, ELE_MICROSTEP);
    #ifdef POLARIZER
        control_po.input = step2deg(stepper_po.currentPosition(), POL_RATIO, POL_MICROSTEP);
    #endif
    // No errors
    if (rotator.rotator_status != error) {
        // Homing flag is false
        if (rotator.homing_flag == false) {
            rotator.control_mode = position;
            // Run homing function
            #ifndef POLARIZER
                rotator.rotator_error = homing(deg2step(-AZI_MAX_ANGLE, AZI_RATIO, AZI_MICROSTEP),
                                           deg2step(-ELE_MAX_ANGLE, ELE_RATIO, ELE_MICROSTEP));
            #else
                rotator.rotator_error = homing(deg2step(-AZI_MAX_ANGLE, AZI_RATIO, AZI_MICROSTEP),
                                           deg2step(-ELE_MAX_ANGLE, ELE_RATIO, ELE_MICROSTEP),
                                           deg2step(-POL_MAX_ANGLE, POL_RATIO, POL_MICROSTEP));
            #endif
            // Respond to homing error
            if (rotator.rotator_error == no_error) {
                rotator.rotator_status = idle;
                rotator.homing_flag = true;
            } 
            else {
                // Error
                rotator.rotator_status = error;
                rotator.rotator_error = homing_error;
            }
        } 
        else {  // Homing flag is true
            #ifndef POLARIZER
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
            #else
                control_po.setpoint = (polPot / 1023.0) * POL_MAX_ANGLE;   // setpoint is the pot proportion of step range
                stepper_az.moveTo(deg2step(control_az.setpoint, AZI_RATIO, AZI_MICROSTEP));
                stepper_el.moveTo(deg2step(control_el.setpoint, ELE_RATIO, ELE_MICROSTEP));
                stepper_po.moveTo(deg2step(control_po.setpoint, POL_RATIO, POL_MICROSTEP));
                rotator.rotator_status = pointing;
                // Move azimuth and elevation motors
                stepper_az.run();
                stepper_el.run();
                stepper_po.run();
                // Idle rotator
                if (stepper_az.distanceToGo() == 0 && stepper_el.distanceToGo() == 0 && stepper_po.distanceToGo() == 0) {
                    rotator.rotator_status = idle;
                }
            #endif
        }
    } 
    else {  // Error handler: stop motors and disable the motor drivers
        stepper_az.stop();
        stepper_az.disableOutputs();
        stepper_el.stop();
        stepper_el.disableOutputs();
        #ifdef POLARIZER
            stepper_po.stop();
            stepper_po.disableOutputs();           
        #endif
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
// Function without polarizer feature enabled
#ifndef POLARIZER
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
                
            // Update WDT
            #ifdef WATCHDOG
                wdt.watchdog_reset();
            #endif
            
            #ifndef DEBUG
                // LED heartbeat: fast blink while homing
                if(ledExists && millis() - ledTime > ledPeriod/6)   {
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
        }


        // Delay to Deccelerate and homing, to complete the movements
        uint32_t time = millis();
        while (millis() - time < HOME_DELAY) {
            wdt.watchdog_reset();
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
// Polarizer feature is enabled
#else
    enum _rotator_error homing(int32_t seek_aziMin, int32_t seek_eleMin, int32_t seek_polMin) {
        bool isHome_az = false;
        bool isHome_el = false;
        bool isHome_po = false;

        // Move motors to "seek" position
        stepper_az.moveTo(seek_aziMin);
        stepper_el.moveTo(seek_eleMin);
        stepper_po.moveTo(seek_polMin);

        // Homing loop
        while (isHome_az == false || isHome_el == false || isHome_po == false) {
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
            if (switch_polMin.get_state() == true && !isHome_po) {
                // Found elevation home
                stepper_po.moveTo(stepper_po.currentPosition());
                isHome_po = true;
            }
            // Check if the rotator goes out of limits or something goes wrong (in
            // mechanical)
            if ((stepper_az.distanceToGo() == 0 && !isHome_az) ||
                (stepper_el.distanceToGo() == 0 && !isHome_el) ||
                (stepper_po.distanceToGo() == 0 && !isHome_po)){
                return homing_error;
            }
            // Move motors
            stepper_az.run();
            stepper_el.run();
            stepper_po.run();
                
            // Update WDT
            #ifdef WATCHDOG
                wdt.watchdog_reset();
            #endif
            
            #ifndef DEBUG
                // LED heartbeat: fast blink while homing
                if(ledExists && millis() - ledTime > ledPeriod/6)   {
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
        }


        // Delay to Deccelerate and homing, to complete the movements
        uint32_t time = millis();
        while (millis() - time < HOME_DELAY) {
            wdt.watchdog_reset();
            stepper_az.run();
            stepper_el.run();
            stepper_el.run();
        }
        // Set the home position and reset all critical control variables
        stepper_az.setCurrentPosition(0);
        stepper_el.setCurrentPosition(0);
        stepper_po.setCurrentPosition(0);
        control_az.setpoint = 0;
        control_el.setpoint = 0;
        control_po.setpoint = 0;

        return no_error;
    }
#endif
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
    return (ratio * SPR * microsteps * deg / 360.0);
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
