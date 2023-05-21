# Project description

With this project you can check if a switch connect to the ports below was pressed.
You can specify which switch you want to check (there is a physical problem with SW2 at this moment).
Pressing the specified switch, the 4 lights LED_RED_M, LED_GREEN_M, LED_BLUE_M and LED_BLUE will loop as long as the switch is pressed. At the same time at the VCP you'll see the status of all 8 ports on the IO_Extender.

SW2, LED_RED_M, LED_GREEN_M, LED_BLUE_M, LED_BLUE, GPIO2A, GPIO2B, J1100_1

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
