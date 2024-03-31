# Expected result

UNDER CONSTRUCTION

# Project setup and configuration

The following changes have been made to \_prj_template.ioc.

## configuration

- PINOUT & CONFIGURATION

- Set PB12 to GPIO_OUTPUT, userlabel to OLED_RESET
  - SYSTEM CORE
    - GPIO
      - PB12
        - GPIO OUTPUT LEVEL: LOW
  - TIMERS
    - LPTIM1
      - MODE
        - COUNTS INTERNAL CLOCK EVENTS
      - PARAMETER SETTINGS
        - CLOCK
          - CLOCK PRESCALAR: PRESCALAR DIV8
      - NVIC SETTINGS
        - LPTIM1 GLOBAL INTERRUPT: ENABLED
  - I2C1
    - PARAMETER SETTINGS
      - CUSTOM TIMING: DISABLED
      - I2C SPEED MODE: STANDARD MODE
      - I2C SPEED FREQUENCIE: 100

[Project setup and configuration](./../Readme.md)
