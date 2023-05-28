# Project description

This project uses a Grove LED strip with at least 10 RGB LED's. It dirst lit all 10 RGB LED's white one by one, after that all 10 LED's will turn RED and GREEN alternating.

Please don't change the sketch to use more than 10 LED's because the GPIO port is not suited for the current these LED's will use.

####

This project does not work for the onboard Serial RGB LEDs (WS2813), because they are not on a timer pin.
