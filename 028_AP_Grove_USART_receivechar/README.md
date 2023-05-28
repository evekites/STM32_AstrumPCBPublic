# Project description

This project waits 6 seconds to receive a character. It then prints a counter, the received character and the corresponding ASCII value both in decimal and in hex.

usart_send.py => PC:COMx => RS232-USB Dongle => Grove to RS232 Sub-D connector => Astrum PCB:USART
=> USB-C VCP => COMy => Serial Console PC
COMx is the COM-port on the RS232-USB dongle and is used by the Python script to send characters
COMy is the COM-port on the USB-C VCP and is used by the Serial Consol application to show the reveived data

##Sample output:
Char26: T ASCII value: 84 0x54
Char27: O ASCII value: 79 0x4f
Char28: d ASCII value: 100 0x64
Timeout: no character received 6 seconds.
Char29: D ASCII value: 68 0x44
