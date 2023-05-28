uint16_t iTeller = 240;
while (1)
{
  char buf[2];

  uint8_t iTellerMSB = (iTeller >> 8) & 0xFF;
  uint8_t iTellerLSB = iTeller & 0xFF;

  buf[0] = iTellerLSB;
  buf[1] = iTellerMSB;
  HAL_UART_Transmit(&huart1, buf, sizeof(buf), 10000);
  HAL_Delay(2000);
  iTeller++;

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */