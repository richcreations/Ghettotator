/*!
* @file watchdog.h
*
* It is a driver for watchdog timer.
*
* Licensed under the GPLv3
*
*/

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <avr/wdt.h>
#include <../lib/globals.h>
#include <../lib/easycomm.h>

/**************************************************************************/
/*!
    @brief    Class that functions for interacting with a watchdog timer
*/
/**************************************************************************/
class wdt_timer{
public:

    /**************************************************************************/
    /*!
        @brief    Initialize watchdog timer to 2sec time out and to set up
                  interrupt routine
    */
    /**************************************************************************/
    void watchdog_init() { 
        cli();
        wdt_reset();
        WDTCSR |= _BV(WDCE) | _BV(WDE); // I'm guessing this is for m328p. test on 1280p appears to work
        WDTCSR = _BV(WDIE) | _BV(WDE) | _BV(WDP3) | _BV(WDP2) | _BV(WDP1);
        sei();
    }

    /**************************************************************************/
    /*!
        @brief    Reset the watchdog timer
    */
    /**************************************************************************/
    void watchdog_reset() {
        wdt_reset();
    }
};

/**************************************************************************/
/*!
    @brief    Watchdog timer interrupt routine that implements a minimal
              easycomm protocol to get the errors and reset the uC
*/
/**************************************************************************/
ISR(WDT_vect) {
    // Disable motors

    digitalWrite(eleENpin, LOW);
    digitalWrite(aziENpin, LOW);
    #ifdef POLARIZER
        digitalWrite(polENpin, LOW);
    #endif
    //digitalWrite(polEN, LOW); //need to write compile time options for these features
    //digitalWrite(tunEN, LOW);
    //digitalWrite(auxEN, LOW);
    // Set error
    rotator.rotator_error = wdt_error;
    rotator.rotator_status = error;
    // Enable interrupts for serial communication
    sei();

    while (1) {
        // Reset the watchdog timer because the interrupts are enabled
        wdt_reset();
        // Implement a minimal easycomm protocol to get the errors and reset uC
    }
}

#endif /* WATCHDOG_H_ */
