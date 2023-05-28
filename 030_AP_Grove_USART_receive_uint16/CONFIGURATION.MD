# Test-setup

Their are 2 diffetent test-setups for this project:

- Test-setup with 2 Astrum PCB's
- Test-setup with 1 Astrum PCB and a PC

## Test setup with 2 Astrum PCB's

For this project you can configure a second Astrum PCB (with 025_AP_Grove_USART_sendchar) as transmitter. Use a Grove cross cable (cross white and yellow, cut the red wire and leave the black wire as is) between the USART ports of the transmitter and the receiver

Astrum PCB1:USART -

## Test setup with 1 Astrum PCB and a PC

For this second test-setup, you'll need the following two cables

- DIY Grove <=> RS232 Sub-D
- USB <=> RS232 Sub-D female

usart_send.py => PC:COMx => RS232-USB Dongle => Grove to RS232 Sub-D connector  
=> Astrum PCB:USART => USB-C VCP => COMy => Serial Console PC

COMx is the COM-port on the RS232-USB dongle and is used by the Python script to send characters  
COMy is the COM-port on the USB-C VCP and is used by the Serial Consol application to show the reveived data

# Configuration

The Grove USART on the Astrum PC is based on RS232 levels (LOW is 12 V and HIGH is -12V).
Beware, don't use an FTDI USB <=> Serial port dongle as is used with Arduino projects, because most of them are based on TTL levels (LOW = 0V, and HIGH is 5V).

- PINOUT & CONFIGURATION
  - Set PB7 to USART_RX
  - Set PB6 to USART_TX
  - Set PC13 to GPIO_OUTPUT, set userlabel to LED_RED
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
