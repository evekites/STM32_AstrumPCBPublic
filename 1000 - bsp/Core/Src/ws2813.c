/*! ***************************************************************************
 *
 * \brief     WS2813 driver
 * \file      ws2813.c
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
#include <stdbool.h>
#include "main.h"

#include "ws2813.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

// This driver assumes TIM2 is running at 64MHz.
//
// The TIM2 counter period is set to 80, which makes a PWM period of
// 1/64MHz * 80 = 1.25us
//
// The following two defines set the output compare values for T0H and T1H:
#define T0H (20-1) // 1/64MHz * 20 = 312.5ns
#define T1H (60-1) // 1/64MHz * 60 = 937.5ns
//
// Given the 1.25us period, this yields:
// T0L = 1.25us - 312.5ns = 937.5ns
// T1L = 1.25us - 937.5ns = 312.5ns
//
// These values are within the ranges as specified in the WS2813 data sheet.

// Add some additional zero bits to the output data. It takes time before the
// DMA interrupt handler is executed and TIM2 will keep on counting and
// generating a PWM signal. By setting some values at the end of the array to
// zero, the PWM signal is low (0% duty cycle) for a while so there is time to
// stop the PWM generation.
#define N_SILENT (8)

// The total number of bits
#define N_BITS ((N_RGB_LEDS * sizeof(rgb_t) * 8) + (N_SILENT))

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
// The Output Compare value for every bit (is the duty cycle of the PWM signal)
// will be stored in an array, so DMA be used to update the output compare
// register.
static uint32_t oc[N_BITS] = {0};

static volatile bool dma_busy = false;

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * Brief Sets the output buffer and initiates a transfer
  *
  * This driver uses TIM2 channel 1 and DMA1 channel 1.
  *
  * Param  data Pointer to the RGB data of length N_RGB_LEDS.
  *
  * Return None
  */
void ws2813_write(const rgb_t *data)
{
    uint32_t cnt=0;

    // Wait for previous transfer to finish
    while(dma_busy == true)
    {}

    // Prepare data
    for(uint32_t i=0; i < N_RGB_LEDS; ++i)
    {
        // Green
        // Loop all 8 bits, MSB first
        for(uint8_t j=0; j < 8; ++j)
        {
            // If the bit is clear, set T0H as output compare, otherwise T1H.
            oc[cnt++] = ((data[i].g & (0x80 >> j)) == 0) ? T0H : T1H;
        }

        // Red
        // Loop all 8 bits, MSB first
        for(uint8_t j=0; j < 8; ++j)
        {
            // If the bit is clear, set T0H as output compare, otherwise T1H.
            oc[cnt++] = ((data[i].r & (0x80 >> j)) == 0) ? T0H : T1H;
        }

        // Blue
        // Loop all 8 bits, MSB first
        for(uint8_t j=0; j < 8; ++j)
        {
            // If the bit is clear, set T0H as output compare, otherwise T1H.
            oc[cnt++] = ((data[i].b & (0x80 >> j)) == 0) ? T0H : T1H;
        }
    }

    // Set remaining silent bits to zero (0% duty cycle)
    for(uint32_t i=0; i < N_SILENT; ++i)
    {
        oc[cnt++] = 0x00;
    }

    // Start data transfer
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, oc, N_BITS);

    // Set DMA busy
    dma_busy = true;
}

/*
 * At the moment, this is the only driver that uses this callback function. If
 * it needs to be used by another driver or the main application, this callback
 * function should probably be relocated to the main application.
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    // Transfer is finished
    HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
    dma_busy = false;
}
