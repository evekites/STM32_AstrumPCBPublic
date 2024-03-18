/*! ***************************************************************************
 *
 * \brief     I2C Scanner
 * \file      i2c_scanner.c
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void I2C_scanner()
{
	uint8_t ret;
	CDC_PRINTF("Scanresults I2C1\r\n");
	for (int i = 1; i < 128; i++)
	{
		ret = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t) (i << 1), 3, 5);
		if (ret == HAL_OK)
		{
			CDC_PRINTF("I2C1: 0x%X\r\n", i);
		}
	}
	CDC_PRINTF("Scanresults I2C3\r\n");
	for (int i = 1; i < 128; i++)
	{
		ret = HAL_I2C_IsDeviceReady(&hi2c3, (uint16_t) (i << 1), 3, 5);
		if (ret == HAL_OK)
		{
			CDC_PRINTF("I2C3: 0x%X\r\n", i);
		}
	}
	CDC_PRINTF("\r\n");
	HAL_Delay(100);
}
