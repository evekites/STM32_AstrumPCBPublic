# Configuration

- PINOUT & CONFIGURATION
  - Set PB2 to GPIO_INPUT, userlabel to SW1
  - Set PC13 to GPIO_OUTPUT, userlabel to LED_RED
  - SYSTEM CORE
    - GPIO
      - NVIC
        - EXTI LINE2 INTERRUPT
          - Check ENABLED
          - PREEMPTION PRIORITY: 1
