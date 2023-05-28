# Project description

For this project you'll need two Astrum PCB's. One of them is the transmitter and the other is the receiver.

The transmitter sends a uint16_t value (16 bits = 2 bytes) to the USART port, but To do this, the uint16_t value needs to be split into two uint8_t values. These values are called the Most Significant Byte (left 8 bits or MSB) and the Least Significant Byte (right 8 bits or LSB). At the receiver side, the MSB and LSB need to be combind to the original uint16_t value.

- Transmitter: Astrum PCB1
  - 029_AP_Grove_USART_send_uint16
- Receiver: Astrum PCB2
  - 028_A030_AP_Grove_USART_receive_uint16P_Grove_USART_receivechar
  - Use a Grove cross cable (cross white and yellow, cut the red wire and leave the black wire as is) between the USART ports of the transmitter and the receiver
  - Use a USB-C <=> USB-A cable to connect the receiver with a computer
  - Open a Serial console application to see the received data.

Transmitter:USART => Grove cross cable => Receiver:USART => USB-C-USB-A VCP => PC:USB (COMy-port) => PC:Serial Console

COMy is the COM-port on the USB-C VCP and is used by the Serial Consol application to show the reveived data

### Sample output:

Nr-4279: MSB: 0, LSB: 248, iTeller: 248  
Nr-4280: MSB: 0, LSB: 249, iTeller: 249  
Nr-4281: MSB: 0, LSB: 250, iTeller: 250  
Nr-4282: MSB: 0, LSB: 251, iTeller: 251  
Nr-4283: MSB: 0, LSB: 252, iTeller: 252  
Nr-4284: MSB: 0, LSB: 253, iTeller: 253  
Nr-4285: MSB: 0, LSB: 254, iTeller: 254  
Nr-4286: MSB: 0, LSB: 255, iTeller: 255  
Nr-4287: MSB: 1, LSB: 0, iTeller: 256  
Nr-4288: MSB: 1, LSB: 1, iTeller: 257  
Nr-4289: MSB: 1, LSB: 2, iTeller: 258  
Nr-4290: MSB: 1, LSB: 3, iTeller: 259
