# Digital Thermometer with Motor Control using PIC18F4620
## Overview
This project demonstrates the implementation of a digital thermometer using the PIC18F4620 microcontroller. The system reads temperatures from two LM35 sensors and controls two motors based on the temperature readings. Additionally, the temperatures are displayed on a 16x4 LCD.
## Hardware Design
![Design](https://github.com/HossamGamalElhelw/Digital-Thermometer-DC-Motor/blob/main/Design.png)
## Components Used
+ PIC18F4620 Microcontroller
-LM35 Temperature Sensors (2 units)
- Motors (2 units)
1 Motor Driver (e.g., L298N or similar)
** 16x4 LCD Display
** L298
## Project Description
** Hardware Setup
Power Supply: A 5V supply powers the PIC18F4620, LM35 sensors, LCD, and motor drivers.
LM35 Sensors: The output pin of each LM35 is connected to the analog input pins of the PIC18F4620.
LM35_1 to AN0 (RA0)
LM35_2 to AN1 (RA1)
Motors and Driver: Control pins of the motor driver are connected to digital output pins of the PIC18F4620.
MOTOR1 control to RB0
MOTOR2 control to RB1
LCD Display: The LCD data pins are connected to PORTC, and control pins (RS, RW, E) are connected to appropriate digital pins on the PIC18F4620.
## Firmware
The firmware is written in C and compiled using the MPLAB XC8 compiler. The key functionalities include:

** ADC Initialization: Sets up the ADC to read analog values from the LM35 sensors.
** Temperature Reading: Converts the ADC values to temperature in Celsius.
** Motor Control: Turns on the motors when the temperature exceeds 36°C.
** LCD Display: Displays the temperature readings on the LCD.
