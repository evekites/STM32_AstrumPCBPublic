# Project description

This project will show the temperature from the onboard temperature sensor on the VCP. The resolution is 0.125 (2^-3) degrees Celsius.

The temperature measured by the sensor is stored in 2 bytes of 8 bits.

- Byte 1 (MSB)

  - b15..b8 contains the two's complement integer part of the temperature
  - In case b15=0 the temperature is positive
  - In case b15=1 the temperature is negative, this is ignored in this project!!

- Byte 0 (LSB)
  - b7..b5 contains the fraction part (0.125 resolution)
  - b4..b0 should be ignored (all zeros)
