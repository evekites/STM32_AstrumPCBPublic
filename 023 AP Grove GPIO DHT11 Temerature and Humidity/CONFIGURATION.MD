# Configuration

- A Grove Temperature and Humidity sensor is connected to GPIO01
- PINOUT & CONFIGURATION
  - Set PB0 to GPIO_OUTPUT
  - SYSTEM CORE
    - GPIO
      - PB0, MAXIMUM OUTPUT SPEED: HIGH

### The followin settings are needed to printf() floating point values

- PROJECT, PROPERTIES
- C/C++ BUILD
- SETTINGS
- MCU SETTINGS
- CHECK "USER FLOAT WITH PRINTF FROM NEWLIB-NANO (-u print_float)

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
int \_write(int file, char _ptr, int len)
{
 CDC_Transmit_FS((uint8_t _)ptr, len);
 return len;
}
```
