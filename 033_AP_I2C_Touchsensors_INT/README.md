# Project description

# This project doesnot work correct, sometimes it works, sometimes is doesn't.

Both SW1 as touching one of the touchpads, will set an Interrupt. The Interrupt callback function will set SW1_ISR or TOUCH_ISR to 1. The main loop will check the value of these variables and will turn LED_RED ON or OFF.
