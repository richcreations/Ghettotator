# Wire Wiggler Firmware: Yet another satellite antenna rotator project
Wire Wiggler is a satellite antenna rotator control firmware intended to be used with common nc controller hardware. The code is based off of satnogs original stepper rotator code.

Read about the original satnogs rotator project here: [SatNOGS Rotator Controller Based on Arduino UNO and CNC V3 Shield](https://wiki.satnogs.org/SatNOGS_Arduino_Uno/CNC_Shield_Based_Rotator_Controller).

## Features
* Interfaces with Hamlib rotctld for easy control with rotator apps like Gpredict
* Homes all axis at boot up
* Watchdog timer shuts down all drivers when triggered
* Optional 3rd axis for polarization control
* ...currently under development

    * IMU feedback for moving vehicles

## Currently Compatible Hardware
* Arduino UNO with CNC Shield v3
* Arduino Mega2560 with Ramps v1.4
* Anet A8 3d Printer Motherboard (1280p w/ built-in a4988's)
* N.O. endstop switches
* Linear potentiometers (use 10nF between wiper and gnd)
* Standard stepper drivers with STEP/DIR/EN pins (eg a4988, drv8825, TMCXXXX in standalone mode)

## Instructions
### Configure, compile, and upload firmware:
*A basic level of understanding on how to comment/edit config files, install and use VSCode, and install and use PlatformIO is assumed in this text.*

Download and decompress the Wire Wiggler repository in your project folder, and open the project in VScode. Edit the `config.h` file to suit your hardware (comment/uncomment and edit any relevant lines). Also edit uncomment the section that matches your microcontroller in `platformio.ini`. Finally select the pio build option that matches your board, and compile+upload to your board. If completed succesfully, your board is now ready for use.

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

## Easycomm Commands
The easycomm lib is used to interface with the computer rotator control software via UART. It allows software like Gpredict to control the rotator. It can also be used to test and troubleshoot rotator hardware by sending commands from a terminal. Here is the list of valid terminal commands that easycomm can respond to (* currently not all commands are implemented):

* AZ, Move azimuth to (degrees 1 decimal place)
* EL, Move elevation to (degrees 1 decimal place)
* SA, Stop azimuth movement
* SE, Stop elevation movement
* RESET, Initiate homing subroutine
* PARK, Move to park position
* IP, Read an input
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
* GS, Get status register
    * idle = 1
    * moving = 2
    * pointing = 4
    * error = 8
* GE, Get error register
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
* CR, Read config... `CR 2 1.0` sets azimuth I gain to 1.0
    * Gain P for AZ = 1
    * Gain I for AZ = 2
    * Gain D for AZ = 3
    * Gain P for EL = 4
    * Gain I for EL = 5
    * Gain D for EL = 6
    * Azimuth park position = 7
    * Elevation park position = 8
    * Control mode (position = 0, speed = 1) = 9
* CW, Write config... `CW 7 0.0` sets azimuth park position to 0.0degrees
    * Gain P for AZ = 1
    * Gain I for AZ = 2
    * Gain D for AZ = 3
    * Gain P for EL = 4
    * Gain I for EL = 5
    * Gain D for EL = 6
    * Azimuth park position = 7
    * Elevation park position = 8

* RB, custom command to reboot controller

## Troubleshooting
Understanding how to stepper motors work in general can help users fix many problems than can arise while operating Wire Wiggler. While it is out of scope to discuss stepper concepts here, it is worthy of note that the mechanics should be as well balanced and friction free as possible.

Wire Wiggler by default uses the onboard LED (if the board has one) to indicate status. A solid on LED means the loop has exited with an error. A slow 1hz flashing LED means the code is running in normal mode (ie ready to be controlled by Gpredict). A fast 5hz flashing LED indicates the code is currently running the homing routine.

## Contribute
The main repository lives on [Github](https://github.com/truglodite/Wire-Wiggler-Firmware).

## License
Licensed under the [GPLv3](LICENSE)
