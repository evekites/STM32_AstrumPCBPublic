# Configuration

For this project you'll need 2 cables

- DIY Grove <=> RS232 Sub-D
- USB <=> RS232 Sub-D female

The Grove USART on the Astrum PC is based on RS232 levels (LOW is 12 V and HIGH is -12V).
Beware, don't use an FTDI USB <=> Serial port dongle as is used with Arduino projects, because most of them are based on TTL levels (LOW = 0V, and HIGH is 5V).

- PINOUT & CONFIGURATION
  - Set PB7 to USART_RX
  - Set PB6 to USART_TX
  - CONNECTIVITY
    - USART1
      - MODE: ASYNCHRONOUS
      - PARAMETER SETTINGS
        - BAUD RATE: 115200;
        - WORD LENGTH: 8 BITS (INCLUDING PARITY)
        - PARITY: NO
        - STOP BITS: 1

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
