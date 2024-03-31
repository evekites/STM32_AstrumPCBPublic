/*! ***************************************************************************
 *
 * \brief     Example buzzer
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int iTempo = 150;
/* External variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
	HAL_Delay(1000);
	int myNotes[] =
	{
	// Ode to Joy – Beethoven’s Symphony No. 9
			NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4, //1
			NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
			NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
			NOTE_E4, -4, NOTE_D4, 8, NOTE_D4, 2,

			NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4, //4
			NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
			NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
			NOTE_D4, -4, NOTE_C4, 8, NOTE_C4, 2,

			NOTE_D4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4, //8
			NOTE_D4, 4, NOTE_E4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_C4, 4,
			NOTE_D4, 4, NOTE_E4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_D4, 4,
			NOTE_C4, 4, NOTE_D4, 4, NOTE_G3, 2,

			NOTE_E4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 4, //12
			NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 4,
			NOTE_C4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4,
			NOTE_D4, -4, NOTE_C4, 8, NOTE_C4, 2
	};

	int iNrOfNotes = sizeof(myNotes) / sizeof(myNotes[0]);
	//sizeoff(myNotes) 						is storage size for myNotes
	//sizeoff(myNotes[0]) 					is storage size for 1 element of myNotes (all elements have same size)
	//sizeof(myNotes) / sizeof(myNotes[0]) 	is number of elements in myNotes

	for (int iTeller = 0; iTeller < iNrOfNotes; iTeller += 2)
	{
		Beep(myNotes[iTeller], myNotes[iTeller + 1]);
	}
	while (1)
	{

	}
}
