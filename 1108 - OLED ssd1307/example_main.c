/*! ***************************************************************************
 *
 * \brief     Example OLED ssd1307
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

#include "ssd1307.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define T_PIXEL_FILL_ANIMATION_ms 2000
#define T_TEXT_SCROLL_ANIMATION_ms 3000

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t millis = 0;

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern LPTIM_HandleTypeDef hlptim1;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
    // hal TIM START IT
    // LPTIM1->ARR = LPTIM1_ARR;
    HAL_LPTIM_Counter_Start_IT(&hlptim1, LPTIM1_ARR);

    if (ssd1307_Init(&DISPLAY0, 0))
        Error_Handler();
    for (int i = 0; i < 4000000; i++)
    {
        __asm("nop");
    }

    while (1)
    {
        /*Test 'Console' function*/
        SSD1307_animation_fill_square(&DISPLAY0, T_PIXEL_FILL_ANIMATION_ms,
                                      White, SSD1307_WIDTH, SSD1307_HEIGHT);
        SSD1307_animation_scroll_text(&DISPLAY0, "Hello Astrum", 5000, White,
                                      SSD1307_HEIGHT / 2 - (Font_11x18.FontHeight / 2), Font_11x18);
        SSD1307_animation_fill_square(&DISPLAY0, T_PIXEL_FILL_ANIMATION_ms,
                                      White, SSD1307_WIDTH, SSD1307_HEIGHT);
        SSD1307_animation_scroll_window(&DISPLAY0, "Hello Astrum", 1000, White,
                                        SSD1307_HEIGHT / 2 - (Font_11x18.FontHeight / 2), Font_11x18);
        SSD1307_animation_fill_square(&DISPLAY0, T_PIXEL_FILL_ANIMATION_ms,
                                      White, SSD1307_WIDTH, SSD1307_HEIGHT);
        SSD1307_println(&DISPLAY0, "auto line 1", White, Font_11x18);
        HAL_Delay(500);
        SSD1307_println(&DISPLAY0, "auto line 2", White, Font_7x10);
        HAL_Delay(500);
        SSD1307_println(&DISPLAY0, "auto line 3", White, Font_11x18);
        HAL_Delay(500);
        SSD1307_println(&DISPLAY0, "auto line 4", White, Font_7x10);
        HAL_Delay(500);
    }
}
