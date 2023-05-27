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
