# Project description

With this project you can check if a switch connect to the ports below was pressed.
You can specify which switch you want to check (there is a physical problem with SW2 at this moment).
Pressing the specified switch, the 4 lights LED_RED_M, LED_GREEN_M, LED_BLUE_M and LED_BLUE will loop as long as the switch is pressed.

At the same time the status of all 8 ports on the IO_Extender (LED's an switches) will be show on the VCP.

0 SW2
1 LED_RED_M
2 LED_GREEN_M
3 LED_BLUE_M
4 LED_BLUE
5 GPIO2A
6 GPIO2B
7 J1100_1

SW2 has a PULL_UP resistor, so pressing it, its status will become 0 (Their is a hardware issue with SW2, after pressing, its status will remain 0 up until a reset!!!)
GPIO2A, GPIO2B, most GROVE Switch modules has a PULL_DOWN resistor, so pressing it, its status will become 1

```
#define SWITCH GPIO2A
#if SWITCH == SW2
  		if (!CheckPin(SW2))
  #elif SWITCH == GPIO2A
  		if (CheckPin(GPIO2A))
  #elif SWITCH == GPIO2B
		if (CheckPin(GPIO2B))
#elif SWITCH == J1100_1
  		if (CheckPin(J1100_1))
#endif
```
