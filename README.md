# Wire Wiggler Firmware: Yet another satellite antenna rotator project
This is a fork of the satnogs stepper rotator firmware that aims clean up the code, port it for use with a broad assortment of hardware, and develop new features like polarization control.

Read about the original satnogs rotator project here: [SatNOGS Rotator Controller Based on Arduino UNO and CNC V3 Shield](https://wiki.satnogs.org/SatNOGS_Arduino_Uno/CNC_Shield_Based_Rotator_Controller).

## Features
* Interfaces with Hamlib rotctld for easy control with rotator apps like Gpredict
* Homes all axis at boot up
* Watchdog timer shuts down all drivers when triggered
* Optional 3rd axis for polarization control

## Currently Compatible Hardware
* Arduino UNO with CNC Shield v3
* Arduino Mega2560 with Ramps v1.4
* Anet A8 3d printer motherboard w/ m1280p and built-in a4988's

## Instructions
### Install Hamlib and Gpredict Software:
Hamlib contains the `rotctld` driver that is used for communication between the rotator control software of your choice (ie Gpredict) and your board's usb or serial port. Details on downloading, installing, and extensively operating GPredict or other control software are beyond the scope of this project. However the process is typically fairly easy to follow.

### Create a launch script for rotctld:
Plug your hardware into your computer, and find the port used by your board using device manager in Windows, or `dmesg | grep tty` in a Linux terminal. This port might be for example `COM3` in windows, or `/dev/ttyUSB3` in Linux. Use this info to make a shell script to launch rotctld using appropriate port (`/dev/ttyUSB0` in this example) in your favorite text editor (ie Notepad++):

```
rotctld -m 202 -r /dev/ttyUSB0 -s 9600 -T 127.0.0.1 -t 4533 -C timeout=500 -C retry=0 -vvvvvvvv
```
Make the script executable so you can use convenient shortcuts to start rotctld before using your rotator software. You can also just use that line in a terminal to start rotctld manually.

### Configure GPredict
In Gpredict, go to Edit > Preferences > Interfaces > Rotators > Add New

Give it a name, for example "Wire Wiggler". Leave the defaults alone (localhost, port 4533). 

### Operating
First use the terminal or startup script to launch rotctld. Now open Gpredict, go to the Rotator Controller, click the enable rotator button, select a satellite to track in the drop down menu, and hit track. That's it... the rotator should start following the sat from AOS to LOS. After reaching LOS, the rotator will move to the next predicted AOS location for the satellite.

## Easycomm implemantation
The easycomm lib is used to interface with the computer rotator control software via UART. Here is the list of valid serial commands that easycomm can respond to (* currently not all commands are implemented):

* AZ, Azimuth, number - 1 decimal place [deg]
* EL, Elevation, number - 1 decimal place [deg]
* SA, Stop azimuth moving
* SE, Stop elevation moving
* RESET, Move to home position
* PARK, Move to park position
* IP, Read an input, number
    * Temperature = 0
    * SW1 = 1
    * SW2 = 2
    * Encoder1 = 3
    * Encoder2 = 4
    * Load of M1/AZ = 5
    * Load of M2/EL = 6
    * Speed of M1/AZ (DPS) = 7
    * Speed of M2/EL (DPS) = 8
* VE, Request Version
* GS, Get status register, number
    * idle = 1
    * moving = 2
    * pointing = 4
    * error = 8
* GE, Get error register, number
    * no_error = 1
    * sensor_error = 2
    * homing_error = 4
    * motor_error = 8
    * over_temperature = 12
    * wdt_error = 16
* VL, Velocity Left ,number [mdeg/s]
* VR, Velocity Right, number [mdeg/s]
* VU, Velocity Up, number [mdeg/s]
* VD, Velocity Down, number [mdeg/s]
* CR, Read config, register [0-x]
    * Gain P for M1/AZ = 1
    * Gain I for M1/AZ = 2
    * Gain D for M1/AZ = 3
    * Gain P for M2/EL = 4
    * Gain I for M2/EL = 5
    * Gain D for M2/EL = 6
    * Azimuth park position = 7
    * Elevation park position = 8
    * Control mode (position = 0, speed = 1) = 9
* CW, Write config, register [0-x]
    * Gain P for M1/AZ = 1
    * Gain I for M1/AZ = 2
    * Gain D for M1/AZ = 3
    * Gain P for M2/EL = 4
    * Gain I for M2/EL = 5
    * Gain D for M2/EL = 6
    * Azimuth park position = 7
    * Elevation park position = 8
    * This reg is set from Vx commands control mode (position = 0, speed = 1) = 9
* RB, custom command to reboot controller

## Contribute

The main repository lives on [Github](https://github.com/truglodite/satnogs-rotator-firmware) and all Merge Request should happen there.

## License

[![Libre Space Foundation](https://img.shields.io/badge/%C2%A9%202014--2018-Libre%20Space%20Foundation-6672D8.svg)](https://librespacefoundation.org/)

Licensed under the [GPLv3](LICENSE)
