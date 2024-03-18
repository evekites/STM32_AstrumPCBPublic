/*! ***************************************************************************
 *
 * \brief     ws2812 driver
 * \file      ws2812.c
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
#include "main.h"
#include "ws2812.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#define WS2812_LED_MAX 10
uint8_t LED_Data[WS2812_LED_MAX][4];
int datasentflag = 0;

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void ws2812_Set_LED(int LEDnum, int Red, int Green, int Blue)
{
  LED_Data[LEDnum][0] = LEDnum;
  LED_Data[LEDnum][1] = Green;
  LED_Data[LEDnum][2] = Red;
  LED_Data[LEDnum][3] = Blue;
}

void ws2812_SetAll_LED(int Red, int Green, int Blue)
{
  for (int i = 0; i < WS2812_LED_MAX; i++)
  {
    ws2812_Set_LED(i, Red, Green, Blue);
  }
}

void ws2812_Send_PWM(void)
{
  uint16_t pwmData[24 * (WS2812_LED_MAX) + 50];
  uint32_t indx = 0;
  uint32_t color;
  for (int i = 0; i < WS2812_LED_MAX; i++)
  {
    color = ((LED_Data[i][1] << 16) | (LED_Data[i][2] << 8) | (LED_Data[i][3]));
    for (int i = 23; i >= 0; i--)
    {
      if (color & (1 << i))
      {
        pwmData[indx] = 53; // 2/3 of ARR=80
      }

      else
        pwmData[indx] = 27; // 1/3 of ARR=80

      indx++;
    }
  }
  for (int i = 0; i < 50; i++)
  {
    pwmData[indx] = 0;
    indx++;
  }
  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)pwmData, indx);
  while (!datasentflag)
  {
  };
  datasentflag = 0;
  HAL_Delay(0); // To prevent weird behaviour
}
