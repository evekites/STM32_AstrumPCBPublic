# Expected result

- Turning the rotary encoder, a counter will be incremented/decremented
- When the counter <=0, led_red will be on
- Pressing the rotary encoder, the counter will be reset to 0 (and led_red will turn on)

# Project setup and configuration

The following changes have been made to \_prj_template.ioc.

# Configuration

- PINOUT & CONFIGURATION
  - Set PC11 tp GPIO_EXTI11, userlabel to ROTARY1
  - Set PC12 tp GPIO_EXTI12, userlabel to ROTARY2
  - SYSTEM CORE
    - GPIO
      - GPIO
        - PC11
          - GPIO MODE: EXTERNAL INTERRUPT MODE WITH RISING/FALING EDGE TRIGGER DETECTION
        - PC12
          - GPIO MODE: EXTERNAL INTERRUPT MODE WITH RISING/FALING EDGE TRIGGER DETECTION
      - NVIC
        - EXTI LINE [15:10] INTERRUPTS: ENABLED
    - NVIC
      - EXTI LINE [15:10] INTERRUPTS: ENABLED

[Project setup and configuration](./../Readme.md)
