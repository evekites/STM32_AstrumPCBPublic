/*! ***************************************************************************
 *
 * \brief     Example 102 - rotary
 * \file      example_main.c
 * \author    Erik Verberne
 * \date      March 2024
 *
 * \copyright 2024 Astrum College. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

/* Private includes ----------------------------------------------------------*/
#include <example_main.h>
#include "main.h"
#include "io_extender.h"
#include "led_red.h"
#include "rotary.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int iPreviousTeller = 0;
int iTeller = 0;

/* External variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{

	while (1)
	{
		if (rotary_pressed())
		{
			iTeller = 0;
		}
		if (iPreviousTeller != iTeller)
		{
			iPreviousTeller = iTeller;
			HAL_Delay(10);
		}
		if (iTeller <= 0)
		{
			led_red_on();
		}
		else
		{
			led_red_off();
		}
	}
}

/*
 Rotary Encoder Interrupt Handler
 Channel A (IRQ12) & B (IRQ11)

 CW --->
 A (IRQ12)  ¯|___|¯¯¯¯|___|¯¯¯¯
 Interrupts  ^   ^    ^   ^
 B (IRQ 11) ¯¯¯|___|¯¯¯¯¯|___|¯
 Interrupts    ^   ^     ^   ^
 CCW <---
 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == ROTARY1_Pin || GPIO_Pin == ROTARY2_Pin)
	{
		static int8_t states[] =
		    {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
		static uint8_t RotaryCurrentState = 0x00;
		static uint8_t RotaryTransition = 0;
		static int8_t RotaryPosition = 0;
		RotaryCurrentState = (HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin) << 1) | HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin);
		RotaryTransition = (RotaryTransition << 2) | RotaryCurrentState;
		RotaryPosition = RotaryPosition + states[RotaryTransition & 0x0F];
		if (RotaryPosition == 4)
		{
			iTeller++;
			RotaryPosition = 0;
		}
		if (RotaryPosition == -4)
		{
			iTeller--;
			RotaryPosition = 0;
		}
	}
}
