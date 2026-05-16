/*
Easycomm antenna rotator library, for interfacing rotator devices with Gpredict etc.
AFAIK, this is the only noticeable blocking in Wire Wiggler. Blocking is very minor
and results in slight motor stuttering during larger moves even with baud 57600.

Easycomm is compatible with the "satnogs" type device found in most rotator apps.
*/

#ifndef LIBRARIES_EASYCOMM_H_
#define LIBRARIES_EASYCOMM_H_

#include <Arduino.h>
#include <avr/wdt.h>
#include "globals.h"

#define BUFFER_SIZE   256   // Set the size of serial buffer (256)

class easycomm {
public:

    void easycomm_init() {
	    Serial.begin(BAUDRATE);
    }

    void easycomm_proc() {
        char buffer[BUFFER_SIZE];
        char incomingByte;
        char *Data = buffer;
        char *rawData;
        static uint16_t BufferIndex = 0;
        char data[100];

        // Block if serial buffer has data
        while (Serial.available() > 0) {
            // read oldest byte
            incomingByte = Serial.read();

            // Buffer var has a complete packet to process
            if (incomingByte == '\n' || incomingByte == '\r') {
                buffer[BufferIndex] = 0;
                if (buffer[0] == 'A' && buffer[1] == 'Z') {
                    if (buffer[2] == ' ' && buffer[3] == 'E' &&
                        buffer[4] == 'L') {
                        // Send current absolute position in deg
                        printAzEl();
                    } else {
                        // Get the absolute position in deg for azimuth
                        rotator.control_mode = position;
                        rawData = strtok_r(Data, " ", &Data);
                        strncpy(data, rawData + 2, 10);
                        if (isNumber(data)) {
                            control_az.setpoint = constrain(atof(data), AZI_MIN_ANGLE, AZI_MAX_ANGLE);
                        }
                        // Get the absolute position in deg for elevation
                        rawData = strtok_r(Data, " ", &Data);
                        if (rawData[0] == 'E' && rawData[1] == 'L') {
                            strncpy(data, rawData + 2, 10);
                            if (isNumber(data)) {
                                control_el.setpoint = constrain(atof(data), ELE_MIN_ANGLE, ELE_MAX_ANGLE);
                            }
                        }
                    }
                } else if (buffer[0] == 'E' && buffer[1] == 'L') {
                        // Get the absolute position in deg for elevation
                        rotator.control_mode = position;
                        rawData = strtok_r(Data, " ", &Data);
                        if (rawData[0] == 'E' && rawData[1] == 'L') {
                            strncpy(data, rawData + 2, 10);
                            if (isNumber(data)) {
                                control_el.setpoint = constrain(atof(data), ELE_MIN_ANGLE, ELE_MAX_ANGLE);
                            }
                        }
                } else if (buffer[0] == 'V' && buffer[1] == 'U') {
                    // Elevation increase speed in mdeg/s
                    rotator.control_mode = speed;
                    strncpy(data, Data + 2, 10);
                    if (isNumber(data)) {
                        // Convert to deg/s
                        control_el.setpoint_speed = atof(data) / 1000;
                    }
                } else if (buffer[0] == 'V' && buffer[1] == 'D') {
                    // Elevation decrease speed in mdeg/s
                    rotator.control_mode = speed;
                    strncpy(data, Data + 2, 10);
                    if (isNumber(data)) {
                        // Convert to deg/s
                        control_el.setpoint_speed = - atof(data) / 1000;
                    }
                } else if (buffer[0] == 'V' && buffer[1] == 'L') {
                    // Azimuth increase speed in mdeg/s
                    rotator.control_mode = speed;
                    strncpy(data, Data + 2, 10);
                    if (isNumber(data)) {
                        // Convert to deg/s
                        control_az.setpoint_speed = atof(data) / 1000;
                    }
                } else if (buffer[0] == 'V' && buffer[1] == 'R') {
                    // Azimuth decrease speed in mdeg/s
                    rotator.control_mode = speed;
                    strncpy(data, Data + 2, 10);
                    if (isNumber(data)) {
                        // Convert to deg/s
                        control_az.setpoint_speed = - atof(data) / 1000;
                    }
                } else if (buffer[0] == 'S' && buffer[1] == 'A' &&
                           buffer[2] == ' ' && buffer[3] == 'S' &&
                           buffer[4] == 'E') {
                    // Stop Moving
                    rotator.control_mode = position;
                    printAzEl();
                    control_az.setpoint = control_az.input;
                    control_el.setpoint = control_el.input;
                } else if (buffer[0] == 'R' && buffer[1] == 'E' &&
                           buffer[2] == 'S' && buffer[3] == 'E' &&
                           buffer[4] == 'T') {
                    // Reset the rotator, go to home position
                    printAzEl();
                    rotator.homing_flag = false;
                } else if (buffer[0] == 'P' && buffer[1] == 'A' &&
                           buffer[2] == 'R' && buffer[3] == 'K' ) {
                    // Park the rotator
                    rotator.control_mode = position;
                    printAzEl();
                    rotator.parking_flag = false;
                } else if (buffer[0] == 'V' && buffer[1] == 'E') {
                    // Get the version of rotator controller
                    Serial.print("VESatNOGS-v2.2\n");
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '0') {
                    // Get the inside temperature
                    Serial.print("IP0,");
                    Serial.print(rotator.inside_temperature, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '1') {
                    // Get the status of end-stop, azimuth
                    Serial.print("IP1,");
                    Serial.print(rotator.switch_eleMin, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '2') {
                    // Get the status of end-stop, elevation
                    Serial.print("IP2,");
                    Serial.print(rotator.switch_aziMin, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '3') {
                    // Get the current position of azimuth in deg
                    Serial.print("IP3,");
                    Serial.print(control_az.input, 2);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '4') {
                    // Get the current position of elevation in deg
                    Serial.print("IP4,");
                    Serial.print(control_el.input, 2);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '5') {
                    // Get the load of azimuth, in range of 0-1023
                    Serial.print("IP5,");
                    Serial.print(control_az.load, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '6') {
                    // Get the load of elevation, in range of 0-1023
                    Serial.print("IP6,");
                    Serial.print(control_el.load, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '7') {
                    // Get the speed of azimuth in deg/s
                    Serial.print("IP7,");
                    Serial.print(control_az.speed, 2);
                    Serial.print('\n');
                } else if (buffer[0] == 'I' && buffer[1] == 'P' &&
                           buffer[2] == '8') {
                    // Get the speed of elevation in deg/s
                    Serial.print("IP8,");
                    Serial.print(control_el.speed, 2);
                    Serial.print('\n');
                } else if (buffer[0] == 'G' && buffer[1] == 'S') {
                    // Get the status of rotator
                    Serial.print("GS");
                    Serial.print(rotator.rotator_status, DEC);
                    Serial.print('\n');
                } else if (buffer[0] == 'G' && buffer[1] == 'E') {
                    // Get the error of rotator
                    Serial.print("GE");
                    Serial.print(rotator.rotator_error, DEC);
                    Serial.print('\n');
                } else if(buffer[0] == 'C' && buffer[1] == 'R') {
                    // Get Configuration of rotator
                    if (buffer[3] == '1') {
                        // Get Kp Azimuth gain
                        Serial.print("1,");
                        Serial.print(control_az.p, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '2') {
                        // Get Ki Azimuth gain
                        Serial.print("2,");
                        Serial.print(control_az.i, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '3') {
                        // Get Kd Azimuth gain
                        Serial.print("3,");
                        Serial.print(control_az.d, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '4') {
                        // Get Kp Elevation gain
                        Serial.print("4,");
                        Serial.print(control_el.p, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '5') {
                        // Get Ki Elevation gain
                        Serial.print("5,");
                        Serial.print(control_el.i, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '6') {
                        // Get Kd Elevation gain
                        Serial.print("6,");
                        Serial.print(control_el.d, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '7') {
                        // Get Azimuth park position
                        Serial.print("7,");
                        Serial.print(rotator.park_az, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '8') {
                        // Get Elevation park position
                        Serial.print("8,");
                        Serial.print(rotator.park_el, 2);
                        Serial.print('\n');
                    } else if (buffer[3] == '9') {
                        // Get control mode
                        Serial.print("9,");
                        Serial.print(rotator.control_mode);
                        Serial.print('\n');
                    }
                } else if (buffer[0] == 'C' && buffer[1] == 'W') {
                    // Set Config
                    if (buffer[2] == '1') {
                        // Set Kp Azimuth gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_az.p = atof(data);
                        }
                    } else if (buffer[2] == '2') {
                        // Set Ki Azimuth gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_az.i = atof(data);
                        }
                    } else if (buffer[2] == '3') {
                        // Set Kd Azimuth gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_az.d = atof(data);
                        }
                    } else if (buffer[2] == '4') {
                        // Set Kp Elevation gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_el.p = atof(data);
                        }
                    } else if (buffer[2] == '5') {
                        // Set Ki Elevation gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_el.i = atof(data);
                        }
                    } else if (buffer[2] == '6') {
                        // Set Kd Elevation gain
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            control_el.d = atof(data);
                        }
                    }  else if (buffer[2] == '7') {
                        // Set the Azimuth park position
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            rotator.park_az = atof(data);
                        }
                    } else if (buffer[2] == '8') {
                        // Set the Elevation park position
                        rawData = strtok_r(Data, ",", &Data);
                        strncpy(data, rawData + 4, 10);
                        if (isNumber(data)) {
                            rotator.park_el = atof(data);
                        }
                    }
                } else if (buffer[0] == 'R' && buffer[1] == 'S'
                        && buffer[2] == 'T') {
                    // Custom command to test the watchdog timer routine
                    while(1);
                } else if (buffer[0] == 'R' && buffer[1] == 'B') {
                    // Custom command to reboot the uC
                    wdt_enable(WDTO_2S);
                    while(1);
                }
                // Reset the buffer and clean the serial buffer
                BufferIndex = 0;
                // Block while sending serial data
                Serial.flush();
            }
            // Store oldest serial byte in buffer var
            else {
                if (BufferIndex < BUFFER_SIZE - 1) {
                    buffer[BufferIndex] = incomingByte;
                    BufferIndex++;
                } else {
                    BufferIndex = 0;
                }
            }
        }
    }

private:
    void printAzEl() {
        Serial.print("AZ");
        Serial.print(control_az.input, 1);
        Serial.print(" EL");
        Serial.print(control_el.input, 1);
        Serial.print('\n');
    }

    bool isNumber(char *input) {
        for (uint16_t i = 0; input[i] != '\0'; i++) {
            if (isalpha(input[i]))
                return false;
        }
        return true;
    }
};

#endif /* LIBRARIES_EASYCOMM_H_ */
