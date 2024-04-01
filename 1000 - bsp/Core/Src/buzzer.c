/*! ***************************************************************************
 *
 * \brief     Buzzer driver
 * \file      buzzer.c
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
#include "notes.h"
/* Private typedef -----------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;

/* Private define ------------------------------------------------------------*/
#define F_CPU 64000000UL

#define BUZZER1_HTIM htim1
#define BUZZER2_HTIM htim1
#define BUZZER1_TIM TIM1
#define BUZZER2_TIM TIM1
#define BUZZER1_CCR CCR1
#define BUZZER2_CCR CCR2
#define BUZZER1_TIM_CHANNEL TIM_CHANNEL_1
#define BUZZER2_TIM_CHANNEL TIM_CHANNEL_2
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern int iTempo;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void Beep(uint16_t frequency, int8_t note)
{
	int16_t duration = 240000 / iTempo / note;
	if (note <0)
	{
		duration = -duration * 1.5;
		//dotted notes are represented with a negative duration and needs to be multiplied by 1.5 and turned positive.
	}

	uint8_t volume = 10; //set max volume to a duty cycle of 49 percent so there is always a deadzone

	if (frequency == 0)
	{
		HAL_Delay(duration);
	}
	else
	{
		HAL_TIM_PWM_Start(&BUZZER1_HTIM, BUZZER1_TIM_CHANNEL);
		HAL_TIM_PWM_Start(&BUZZER2_HTIM, BUZZER2_TIM_CHANNEL);
		BUZZER1_TIM->ARR = (F_CPU / ((BUZZER1_TIM->PSC + 1) * frequency));
		BUZZER2_TIM->ARR = (F_CPU / ((BUZZER2_TIM->PSC + 1) * frequency));

		BUZZER1_TIM->BUZZER1_CCR = (BUZZER1_TIM->ARR * volume) / 100;
		BUZZER2_TIM->BUZZER2_CCR = BUZZER2_TIM->ARR
				- ((BUZZER2_TIM->ARR * volume) / 100);
		HAL_Delay(duration * 0.9); // create room for the silence between two notes

		HAL_TIM_PWM_Stop(&BUZZER1_HTIM, BUZZER1_TIM_CHANNEL);
		HAL_TIM_PWM_Stop(&BUZZER2_HTIM, BUZZER2_TIM_CHANNEL);
		HAL_Delay(duration * 0.1);
		// silence between two notes:
	}

}
