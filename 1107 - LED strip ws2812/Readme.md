# Expected result

- Red chaser, green chaser, blue chaser

# ATTENTION
At this point it is nog possible to use the onboard buzzer, because that components is connected to the same timer, but needs different parameters. Use an external buzzer instead. 

# Project setup and configuration

You should make the following changes to the .ioc file:

# Configuration

A "Grove Neopixel (WS2812) LED strip" is connected to GPIO3 with 10 Neopixels

- PINOUT & CONFIGURATION
  - Set PA10 to TIM1_CH3
  - TIMERS
    - TIM1
      - CLOCK SOURCE: INTERNAL CLOCK
      - CHANNEL 3: PWM GENERATION CH3
      - PARAMETER SETTINGS
        - PRESCALE (PSC - 16 BIT VALUE): 0
        - COUNTER MODE: UP
        - COUNTER PERIOD (AUTO RELOAD REGISTER): 80-1
        - AUTO-RELOAD PRELOAD: DISABLE
- SYSTEM CORE
  - DMA
    - ADD A DMA CHANNEL
      - TIM_CH3
      - DMA1 CHANNEL 1
      - MEMORY TO PERIPHERAL

## Solve the following conflict

The callback function HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef \*htim) in ws2813.h conflicts with the same function in example_main.c (ws2812). The ws2813 source and header files are part of the bsp package.

There are 2 solutions tested for this:

- After copying the bsp package to your project, delete both ws2813.h & ws2813.c
- Comment out the function HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef \*htim) in ws2813.c.

Since both libraries (ws2812 & ws2813) use different timers (htim1 & htim2) to initiate the callback function, you could also combine both callback functions to example_main.c and test which timer has called the callback function. This has not been implemented/tested yet.

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef \*htim)
{
if (htim == &htim1)
{
// callback code for the ws2812
HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
datasentflag = 1;
}
if (htim == &htim2)
{
// callback code for the ws2813
}
}

This project needs a callback function for the timer. The library for the ws2813 also needs a callback for a timer.
[Project setup and configuration](./../Readme.md)
