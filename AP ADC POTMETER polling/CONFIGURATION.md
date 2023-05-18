# Configuration

The following settings are incorporated in the \*.ioc file for this project.

- PINOUT & CONFIGURATION
  - CONNECTIVITY
    - PC1 is set to ADC1_IN2, user label: POTMETER
    - PC13 is set to GPIO_OUTPUT, user label: LED_RED
  - ANALOG
    - ADC1
      - IN2: IN2 SINGLE-ENDED

### This last part is to enable the Virtual Com Port on the USB-C connector (VCP).

- Output will be sent to the USB-C Virtual Com Port (VCP)
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

The following code (see main.c) will redirect printf() statements to the VCP.
int \_write(int file, char _ptr, int len)
{
CDC_Transmit_FS((uint8_t _)ptr, len);
return len;
}
