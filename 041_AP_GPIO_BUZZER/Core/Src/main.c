/* USER CODE BEGIN PD */
#define F_CPU 64000000UL
#define BUZZER1_HTIM htim1
#define BUZZER2_HTIM htim1
#define BUZZER1_TIM TIM1
#define BUZZER2_TIM TIM1
#define BUZZER1_CCR CCR1
#define BUZZER2_CCR CCR2
#define BUZZER1_TIM_CHANNEL TIM_CHANNEL_1
#define BUZZER2_TIM_CHANNEL TIM_CHANNEL_2
/* USER CODE END PD */

/* USER CODE BEGIN PFP */
void SetBuzzerFrequency(uint16_t frequency, uint8_t volume);
/* USER CODE END PFP */

/* USER CODE BEGIN WHILE */
while (1)
{
  SetBuzzerFrequency(4000, 100);
  HAL_Delay(200);
  SetBuzzerFrequency(0, 0);
  HAL_Delay(100);
  SetBuzzerFrequency(4000, 100);
  HAL_Delay(200);
  SetBuzzerFrequency(0, 0);
  HAL_Delay(100);
  SetBuzzerFrequency(4000, 100);
  HAL_Delay(200);
  SetBuzzerFrequency(0, 0);
  HAL_Delay(8000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
/**
 * \brief SetBuzzerFrequency enables and sets the frequency of the buzzer to a certain value
 *
 * \note if input frequency is 0 the pwm buzzer will be stopped.
 * \param frequency in hertz
 * \param volume in percentage 0% - 100%
 */
void SetBuzzerFrequency(uint16_t frequency, uint8_t volume)
{
  volume /= 2;
  if (volume > 45)
  {
    volume -= 1; // set max volume to a duty cycle of 49 percent so there is always a deadzone
  }
  if (frequency == 0)
  {
    HAL_TIM_PWM_Stop(&BUZZER1_HTIM, BUZZER1_TIM_CHANNEL);
    HAL_TIM_PWM_Stop(&BUZZER2_HTIM, BUZZER2_TIM_CHANNEL);
  }
  else
  {
    HAL_TIM_PWM_Start(&BUZZER1_HTIM, BUZZER1_TIM_CHANNEL);
    HAL_TIM_PWM_Start(&BUZZER2_HTIM, BUZZER2_TIM_CHANNEL);
  }
  BUZZER1_TIM->ARR = (F_CPU / ((BUZZER1_TIM->PSC + 1) * frequency));
  BUZZER2_TIM->ARR = (F_CPU / ((BUZZER2_TIM->PSC + 1) * frequency));
  BUZZER1_TIM->BUZZER1_CCR = (BUZZER1_TIM->ARR * volume) / 100;
  BUZZER2_TIM->BUZZER2_CCR = BUZZER2_TIM->ARR - ((BUZZER2_TIM->ARR * volume) / 100);
}