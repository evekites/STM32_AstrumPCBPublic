/*! ***************************************************************************
 *
 * \brief     Example 004 - USB CDC
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
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
    // Delay to give USB the time to enumerate
    HAL_Delay(1000);

    // Print welcome message
    CDC_PRINTF("\r\nC-University\r\n");
    CDC_PRINTF("USB CDC Example\r\n");

    char in[16];
    int num;

    while(1)
    {
        // Ask for a string and check the result
        do
        {
            CDC_PRINTF("Enter a number from 1 to 100\r\n");
            CDC_GETSTR(in);
            num = atoi(in);
            
        }while((num < 1) || (num > 100));

        // Print the result
        CDC_PRINTF("You entered %03d\r\n", num);
    }
}
