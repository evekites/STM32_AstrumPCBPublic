# Expected result

- A counter will run on a "Grove 4 digits 7 segments display" connected to Grove port GPIO01

# Project setup and configuration

You should make the following changes to the .ioc file:

# Configuration

A Grove "Grove 4 digits 7 segments display" (TM1637) is connected to GPIO01

- PINOUT & CONFIGURATION
  - Set PB0 to GPIO_OUTPUT, userlabel to TM1637_CLK
  - Set PB1 to GPIO_OUTPUT, userlabel to TM1637_DIO
  - SYSTEM CORE
    - GPIO
      - PB0, MAXIMUM OUTPUT SPEED: HIGH
      - PB1, MAXIMUM OUTPUT SPEED: HIGH

[Project setup and configuration](./../Readme.md)
