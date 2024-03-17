# Configuration

- PINOUT & CONFIGURATION
  - Set PC13 to GPIO_OUTPUT, userlabel to LED_RED
  - TIMERS, TIM16
    - ACTIVATED
    - PARAMETER SETTINGS
      - PRESCALAR: 32000-1
      - COUNTER PERIOD (AUTO RELOAD REGISTER ...): 2000-1
      - AUTO RELOAD PRELOAD: ENABLE
    - NVIC SETTINGS
      - TIM2 GLOBAL INTERUPT: ENABLED
- CLOCK CONFIGURATION
  - APB1 TIMER CLOCKS: 64 MHz
  - APB2 TIMER CLOCKS: 64 MHz

htim16 ticks once every second.

<mark>
Changing ARR to 4000-1 doubles the duration (to 2s)
Changing ARR to 1000-1 doubles the duration (to 0.5s)
</mark>
