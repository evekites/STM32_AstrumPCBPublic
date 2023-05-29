# Project description

This project is NOT based on the Astrum PCB, but on the GLOW PCB.

The GLOW PCB contains a STM32WB55CCUx microcontroller, an IMU, a USART connector based on the Grove connectors, two different IO_Extenders with a total of 4 High power LED's.

IO_Extender for RGB LED's: TLC5957RTQT
16 Red LED's
16 Green LED's
16 Blue LED's

IO_Extender for White LED's: PCA9955BTWJ
16 White LED's

These LED's are grouped in 8x RGBW LED's per side.

In the endproduct two of these discs will be combined with each 2 18650 rechargeable batteries. So each endproduct will contain 32 groups of RGBW LED's, comming to a total of 128 high power LED's.

IMU
Either a LIS3DHTR or a LSM6DSO32TR.

USART
TTL-level communication with Grove connectors

On chip:
Bluetooth BLE
Zigbee
Proprietary 2.4GHz
