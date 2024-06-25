## LiFi Smart House Security System

## Overview
This project implements a smart house security system using LiFi (Light Fidelity) technology. The system utilizes Tiva C microcontroller for sensor data acquisition and Arduino for receiving alerts via LiFi communication.

## Features
Object Detection and Security: Ultra-sonic sensor for detecting objects, fume sensor for fire detection, and magnetic sensors for doors and windows.
LiFi Communication: Tiva C transmits data to Arduino using a laser module, which Arduino receives via a light sensor.
Alert System: Arduino displays warnings on an LCD screen based on the data received from Tiva C.
Bluetooth Communication: Tiva C sends alerts to a mobile device via Bluetooth using UART communication.

## Components Used
Tiva C Series TM4C123G microcontroller
Arduino Uno
Ultra-sonic sensor
Fume sensor
Magnetic sensors (for doors and windows)
Laser module
Light sensor
Bluetooth module
LCD screen

## Setup
  1- Hardware Setup:

  Connect ultra-sonic sensor, fume sensor, and magnetic sensors to Tiva C.
  Connect laser module and light sensor to Tiva C and Arduino respectively for LiFi communication.
  Connect Arduino to LCD screen for displaying warnings.
  Ensure Bluetooth module is connected to Tiva C for mobile alerts.
  
  2- Software Setup:
  
  Flash Tiva C with the appropriate firmware to read sensor data and transmit warnings.
  Upload Arduino code to interpret LiFi signals and display warnings on LCD.
  Usage
  Power on the system.
  Tiva C monitors sensors for any security breaches or anomalies.
  Upon detection, Tiva C sends warnings via LiFi to Arduino.
  Arduino displays warnings on the connected LCD screen.
  Tiva C also sends alerts to a mobile device via Bluetooth for remote monitoring.

## Future Enhancements

Integration with a centralized smart home system for automated responses.
Enhance sensor capabilities and add more security features.
Improve LiFi communication for faster and more reliable data transmission.
