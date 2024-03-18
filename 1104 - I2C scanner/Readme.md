# Expected result

- Turning the rotary encoder, a counter will be incremented/decremented
- When the counter <=0, led_red will be on
- Pressing the rotary encoder, the counter will be reset to 0 (and led_red will turn on)

# Project setup and configuration

The following changes have been made to \_prj_template.ioc.

# Configuration

- PINOUT & CONFIGURATION
  - Set PB10 to I2C3-SCL
  - Set PB11 to I2C3-SDA
  - CONNECTIVITY
    - I2C3
      - I2C

[Project setup and configuration](./../Readme.md)
