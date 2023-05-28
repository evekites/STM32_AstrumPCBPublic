/* USER CODE BEGIN WHILE */
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
while (1)
{
  int iStand = 20;
  htim1.Instance->CCR3 = iStand; // duty cycle is .5 ms
  HAL_Delay(2000);
  iStand = 50;
  htim1.Instance->CCR3 = iStand; // duty cycle is 1.5 ms
  HAL_Delay(2000);
  iStand = 125;
  htim1.Instance->CCR3 = iStand; // duty cycle is 2.5 ms
  HAL_Delay(2000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */