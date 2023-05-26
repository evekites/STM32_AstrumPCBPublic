# Configuration

- In this sample:
  - 1 or more I2C devices can be added to the I2C Grove ports.
- PINOUT & CONFIGURATION
  - Set PB2 to GPIO_INPUT, userlabel to SW1
  - Set PB8 to I2C1-SCL
  - Set PB9 to I2C1-SDA
  - Set PB10 to I2C3-SCL
  - Set PB11 to I2C3-SDA
  - Set PC13 to GPIO_OUTPUT, userlabel to LED_RED
  - CONNECTIVITY
    - I2C1
      - I2C
    - I2C3
      - I2C

### The following part of the configuration is to enable the Virtual Com Port on the USB-C connector (VCP).

- Output from printf() will be sent to the USB-C Virtual Com Port (VCP)
- Use a serial console application to read the result 115.200, 8, none, 1
- PINOUT & CONFIGURATION
  - CONNECTIVITY
    - USB
      - DEVICE (FS)
  - MIDDLEWARE AND SOFTWARE PACKS
    - USB_DEVICE
      - COMMUNICATION DEVICE CLASS (VIRTUAL PORT COM)
- CLOCK CONFIGURATION
  - RESOLVE CLOCK ISSUES

The following code (see main.c) will redirect printf() statements to the VCP:

```
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
	CDC_Transmit_FS((uint8_t *)ptr, len);
	return len;
}
/* USER CODE END 0 */
```
