/*! ***************************************************************************
 *
 * \brief     Example WS2812 LED strip on GPIO3
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
#include "example_main.h"
#include "main.h"
#include "ws2812.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
// extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;
extern int datasentflag;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
	while (1)
	{
		for (int iLEDnum = 0; iLEDnum < 10; iLEDnum++)
		{
			ws2812_Set_LED(iLEDnum, 30, 0, 0);
			ws2812_Send_PWM();
			HAL_Delay(100);
			ws2812_Set_LED(iLEDnum, 0, 0, 00);
			ws2812_Send_PWM();
		}

		for (int iLEDnum = 0; iLEDnum < 10; iLEDnum++)
		{
			ws2812_Set_LED(iLEDnum, 0, 30, 0);
			ws2812_Send_PWM();
			HAL_Delay(100);
			ws2812_Set_LED(iLEDnum, 0, 0, 00);
			ws2812_Send_PWM();
		}

		for (int iLEDnum = 0; iLEDnum < 10; iLEDnum++)
		{
			ws2812_Set_LED(iLEDnum, 0, 0, 30);
			ws2812_Send_PWM();
			HAL_Delay(100);
			ws2812_Set_LED(iLEDnum, 0, 0, 00);
			ws2812_Send_PWM();
		}
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
		datasentflag = 1;
	}
}
