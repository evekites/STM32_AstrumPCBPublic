# Expected result

- This firmware will plays a simple song once (not in the while(1)-loop).

# Project setup and configuration

The following changes have been made to \_prj_template.ioc.

## configuration

- PINOUT & CONFIGURATION
  - Set PA8 to TIM1_CH1, userlabel to BUZZER1
  - Set PA9 to TIM1_CH2, userlabel to BUZZER2
    ROTARY2
  - TIMERS
    - TIM1
      - Clock Source: Internal Clock
      - Channel 1: PWM Generation CH1
      - Channal 2: PWM Generation CH2
      - Parameter Settings
        - Prescalar (PSC): 4
        - Counter Mode: Center Aligned Mode 1
        - Counter Period (ARR): 30
        - auto-reload preload: Enable

[Project setup and configuration](./../Readme.md)
