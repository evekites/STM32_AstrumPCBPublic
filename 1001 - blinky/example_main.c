/*! ***************************************************************************
 *
 * \brief     Example 001 - Blinky
 * \file      example_main.c
 * \author    Hugo Arends
 * \date      July 2023
 *
 * \copyright 2023 HAN University of Applied Sciences. All Rights Reserved.
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
#include "example_main.h"

#include "io_extender.h"
#include "led_red.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
    const uint32_t delay_ms = 400;

    // The IO extender must be initialized before it is used
    io_extender_init();

    while(1)
    {
        // Blink LED_RED
        led_red_on();
        HAL_Delay(delay_ms);
        led_red_off();

        // Blink LED_RED_M
        led_red_m_on();
        HAL_Delay(delay_ms);
        led_red_m_off();

        // Blink LED_GREEN_M
        led_green_m_on();
        HAL_Delay(delay_ms);
        led_green_m_off();

        // Blink LED_BLUE_M
        led_blue_m_on();
        HAL_Delay(delay_ms);
        led_blue_m_off();

        // Blink LED_BLUE
        led_blue_on();
        HAL_Delay(delay_ms);
        led_blue_off();
    }
}
