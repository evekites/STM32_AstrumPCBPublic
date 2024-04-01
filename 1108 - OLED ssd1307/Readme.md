# Expected result

UNDER CONSTRUCTION

# Project setup and configuration

The following changes have been made to \_prj_template.ioc.

## configuration

- PINOUT & CONFIGURATION

- Set PB12 to GPIO_OUTPUT, userlabel to OLED_RESET
- TIMERS
  - LPTIM1
    - MODE
      - COUNTS INTERNAL CLOCK EVENTS
    - PARAMETER SETTINGS
      - CLOCK
        - CLOCK
          - PRESCALAR: PRESCALAR DIV8
    - NVIC SETTINGS
      - LPTIM1 GLOBAL INTERRUPT: ENABLED

[Project setup and configuration](./../Readme.md)
