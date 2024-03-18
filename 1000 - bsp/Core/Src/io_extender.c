/*! ***************************************************************************
 *
 * \brief     IO Extender driver
 * \file      io_extender.c
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

#include "io_extender.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define I2C_ADDRESS (0x21)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile bool io_extender_int_flag = false;
uint8_t in, out;

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void io_extender_init(void)
{
    // The IO extender features quasi-bidirectional I/Os. This means that each
    // pin is an input or output, without the need of a direction control
    // register. The value returned to master depends on the actual voltage or
    // status of the pin. For every input pin, the master MUST always write a
    // logic 1.
    //
    // The pins are configured as follows:
    //
    // P0: SWITCH2 (input)
    // P1: LED_RED_M (output - active low)
    // P2: LED_GREEN_M (output - active low)
    // P3: LED_BLUE_M (output - active low)
    // P4: LED_BLUE (output - active high)
    // P5: GPIO2A (output)
    // P6: GPIO2B (output)
    // P7: nc (output)
    out = 0b11101111;
    in  = 0b00000000;

    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_red_m_on(void)
{
    // LED_RED_M is active low
    out &= ~0b00000010;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_red_m_off(void)
{
    // LED_RED_M is active low
    out |= 0b00000010;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_red_m_toggle(void)
{
    out ^= 0b00000010;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_green_m_on(void)
{
    // LED_GREEN_M is active low
    out &= ~0b00000100;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_green_m_off(void)
{
    // LED_GREEN_M is active low
    out |= 0b00000100;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_green_m_toggle(void)
{
    out ^= 0b00000100;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_m_on(void)
{
    // LED_BLUE_M is active low
    out &= ~0b00001000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_m_off(void)
{
    // LED_BLUE_M is active low
    out |= 0b00001000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_m_toggle(void)
{
    out ^= 0b00001000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_on(void)
{
    // LED_BLUE is active high
    out |= 0b00010000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_off(void)
{
    // LED_BLUE is active high
    out &= ~0b00010000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

void led_blue_toggle(void)
{
    out ^= 0b00010000;
    HAL_I2C_Master_Transmit(&hi2c1, (I2C_ADDRESS<<1), &out, 1, HAL_MAX_DELAY);
}

bool sw2_pressed(void)
{
    // Has there been an IO extender interrupt?
    if(io_extender_int_flag == true)
    {
        // Yes, reset the flag
        io_extender_int_flag = false;

        // Get data from IO extender
        HAL_I2C_Master_Receive(&hi2c1, ((I2C_ADDRESS<<1) | 1), &in, 1, HAL_MAX_DELAY);

        // Return state of the SW2 pin connected to P0
        return !(in & 0b00000001);
    }

    return false;
}
