# Configuration

- PINOUT & CONFIGURATION
  - Set PA10 to TIM1_CH3, userlabel to BUZZER_GROVE
  - TIMERS
    - TIM1
      - CLOCK SOURCE: INTERNAL CLOCK
      - CHANNEL 3: PWM GENERATION CH3
      - PARAMETER SETTINGS:
        - PRESCALER: 83
        - COUNTER PERIOD (AUTO RELOAD REGISTER): 255
        - AUTOLOAD RELOAD: ENABLE
  - CLOCK CONFIGURATION
    - APB1 TIMER CLOCKS: 8
    - APB2 TIMER CLOCKS: 8

### !!Note!!

I'm not sure wheter these timer settings are correct and what the relation is between the ARR (AUTO RELOAD REGISTER) and the values used for iCounter in the loop.
