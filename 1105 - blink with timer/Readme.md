# Expected result

- This example togles led_red once per 2 seconds.

# Project setup and configuration

You should make the following changes to the .ioc file:

# Configuration

- PINOUT & CONFIGURATION
  - TIMERS, TIM16
    - ACTIVATED
    - PARAMETER SETTINGS
      - PRESCALAR: 32000-1
      - COUNTER PERIOD (AUTO RELOAD REGISTER ...): 4000-1
      - AUTO RELOAD PRELOAD: ENABLE
    - NVIC SETTINGS
      - TIM2 GLOBAL INTERUPT: ENABLED
- CLOCK CONFIGURATION
  - APB1 TIMER CLOCKS: 64 MHz
  - APB1 TIMER CLOCKS: 64 MHz

htim16 ticks once every 2 seconds.

Changing ARR to 8000-1 doubles the duration to 4s
Changing ARR to 2000-1 halves the duration to 1s

[Project setup and configuration](./../Readme.md)
