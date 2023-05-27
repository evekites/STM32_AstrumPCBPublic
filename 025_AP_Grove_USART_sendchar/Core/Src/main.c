/* USER CODE BEGIN WHILE */
while (1)
{
  char buf[1];
  buf[0] = 13; // '\r'	Carriage Return
  HAL_UART_Transmit(&huart1, buf, sizeof(buf), 10000);
  HAL_Delay(200);
  buf[0] = 10; // '\n'	Linefeed
  HAL_UART_Transmit(&huart1, buf, sizeof(buf), 10000);
  HAL_Delay(200);
  //'A' = 65
  //'Z' = 90
  for (char iCounter = 65; iCounter <= 90; iCounter++)
  {
    buf[0] = iCounter;
    HAL_UART_Transmit(&huart1, buf, sizeof(buf), 10000);
    HAL_Delay(200);
  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */