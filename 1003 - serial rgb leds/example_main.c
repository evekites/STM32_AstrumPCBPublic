/*! ***************************************************************************
 *
 * \brief     Example 003 - Serial RGB LEDs
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
#include <example_main.h>
#include "main.h"
#include "ws2813.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
    // At startup, the first RGB LED will briefly blink. This is caused by the
    // pin being pulled low after a microcontroller reset.

    // All LEDs off
    rgb_t leds[N_RGB_LEDS] = {0};
    ws2813_write(leds);

    // Set the intensity
    const uint8_t intensity = 20;
    const uint32_t delay_ms = 150;

    while(1)
    {
        // Green chaser
        for(uint32_t i=0; i<N_RGB_LEDS; i++)
        {
            leds[i].g = intensity*2;
            ws2813_write(leds);
            HAL_Delay(delay_ms);
            leds[i].g = 0;
        }

        // Red chaser
        for(uint32_t i=0; i<N_RGB_LEDS; i++)
        {
            leds[i].r = intensity;
            ws2813_write(leds);
            HAL_Delay(delay_ms);
            leds[i].r = 0;
        }

        // Blue chaser
        for(uint32_t i=0; i<N_RGB_LEDS; i++)
        {
            leds[i].b = intensity;
            ws2813_write(leds);
            HAL_Delay(delay_ms);
            leds[i].b = 0;
        }
    }
}
