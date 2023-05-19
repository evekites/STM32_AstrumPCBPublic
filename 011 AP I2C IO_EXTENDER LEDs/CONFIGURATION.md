# Configuration

- PINOUT & CONFIGURATION

  - Set PB8 to I2C1-SCL
  - Set PB9 to I2C1-SDA

  - CONNECTIVITY
    - I2C1
      - I2C

### The following part of the configuration is to enable the Virtual Com Port on the USB-C connector (VCP).
The only output in this project is generated when there is an I2C error.

- Output from printf() will be sent to the USB-C Virtual Com Port (VCP).
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
int \_write(int file, char _ptr, int len)
{
 CDC_Transmit_FS((uint8_t _)ptr, len);
 return len;
}
```
