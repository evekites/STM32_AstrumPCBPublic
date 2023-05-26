/* USER CODE BEGIN WHILE */
while (1)
{
  const ledOn = 400;
  const ledOff = 100;
  HAL_GPIO_TogglePin(GPIO1A_GPIO_Port, GPIO1A_Pin);
  HAL_Delay(ledOn);
  HAL_GPIO_TogglePin(GPIO1A_GPIO_Port, GPIO1A_Pin);
  HAL_Delay(ledOff);

  HAL_GPIO_TogglePin(GPIO1B_GPIO_Port, GPIO1B_Pin);
  HAL_Delay(ledOn);
  HAL_GPIO_TogglePin(GPIO1B_GPIO_Port, GPIO1B_Pin);
  HAL_Delay(ledOff);

  HAL_GPIO_TogglePin(GPIO3A_GPIO_Port, GPIO3A_Pin);
  HAL_Delay(ledOn);
  HAL_GPIO_TogglePin(GPIO3A_GPIO_Port, GPIO3A_Pin);
  HAL_Delay(ledOff);

  HAL_GPIO_TogglePin(GPIO3B_GPIO_Port, GPIO3B_Pin);
  HAL_Delay(ledOn);
  HAL_GPIO_TogglePin(GPIO3B_GPIO_Port, GPIO3B_Pin);
  HAL_Delay(ledOff);

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */