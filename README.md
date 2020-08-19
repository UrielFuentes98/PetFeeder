# PetFeeder
Automatic pet feeder. Code for a PIC12F683 to control a servo motor to release pet food from a container.

## Description
The system can be programmed to dispense food once, twice or three times a day. A push button is used to enter the programming mode and program the feed frequency. The frequency is changed with a potentiometer and is informed by three LEDs. The food is dispensed by rotating a servo about 15° and returning it back to its home position. A CD with a hole is glued with the servo. So when the servo goes to 15° the CD's hole and the container's hole align allowing food to go out. 

## Build
I built the project with MPLAB X using the XC8 compiler. Just compile the main file. I program the micro with a PICKit3
