# Project description

When you touch one of the touchsensors, the corresponding status bit in the I2C register address will turn to 1 and LED_RED will turn on. The status bit will stay 1 until the I2C register has been reset. This is done by pressing the SW1 button.

The status of the I2C register address will be shown on the VCP.
