# Project description

This project is basicaly the same as 028_AP_Grove_USART_receivechar, but this project uses the interrupt on USART_Rx to receive a character from a transmitter. It then prints the following information the the VCP:

- a receive counter
- the received character
- the ASCII value in decimal
- the ASCII value in hex

## Two different setups possible

- Astrum PCB as transmitter
- PC (python script) as transmitter

### Astrum PCB as transmitter

- Transmitter: Astrum PCB1
  - 025_AP_Grove_USART_sendchar
  - Grove cross cable (cross white and yellow, cut the red wire and leave the black wire as is)
- Receiver: Astrum PCB2
  - 037_AP_Grove_USART_receivechar_INT
  - USB-C <=> USB-A cable to connect the receiver with a computer
  - Open a Serial console application to see the received data.

Transmitter:USART => Grove cross cable => Receiver:USART => USB-C-USB-A VCP => PC:USB (COMy-port) => PC:Serial Console

COMy is the COM-port on the USB-C VCP and is used by the Serial Consol application to show the reveived data

### PC (python script) as transmitter

- Transmitter: PC
  - 027_usart_send.py on COMx
- Receiver: Astrum PCB2
  - 037_AP_Grove_USART_receivechar_INT
  - Grove to RS232 Sub-D connector
  - RS232-USB dongle
  - Serial Console on COMy

Transmitter => PC:COMx => RS232-USB Dongle => Grove to RS232 Sub-D connector  
=> Receiver:USART => USB-C VCP => PC:USB (COMx-port) => PC:Serial Console

COMx is the COM-port on the RS232-USB dongle and is used by the Python script to send characters  
COMy is the COM-port on the USB-C VCP and is used by the Serial Consol application to show the reveived data

## Sample output:

Char26: T ASCII value: 84 0x54  
Char27: O ASCII value: 79 0x4f  
Char28: d ASCII value: 100 0x64  
Timeout: no character received 6 seconds.  
Char29: D ASCII value: 68 0x44
