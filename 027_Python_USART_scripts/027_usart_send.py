# this Python 3.x script sends a random letter to a COM port, with a random interval 1 .. 12 seconds
# You will need python 3.6 or higher and the pyserial module:  pip install pyserial
# start this script with:  python usart_send.py from the commandline
import random
import serial
import string
import time

ser = serial.Serial("COM28", 115200, timeout=0.050)
count = 0

while 1:
    randomLetter = random.choice(string.ascii_letters)
    randomInterval = 1  # random.randint(1, 12)
    ser.write(bytearray(randomLetter, "ascii"))
    print(f"Char{count}: {randomLetter}")
    time.sleep(randomInterval)
    count += 1
