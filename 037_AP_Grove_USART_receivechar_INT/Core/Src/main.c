/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN WHILE */
int iCounter = 0;
while (1)
{
  uint8_t buf[1];
  if (HAL_UART_Receive(&huart1, buf, 1, 6000) == HAL_OK) // haal 1 character
  {
    printf("Char%d: %c  ASCII value: %d  0x%x\r\n", iCounter, buf[0], buf[0], buf[0]);
    iCounter++;
    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin); // toggle LED als er data is ontvangen of na timout
  }
  else
  {
    printf("Timeout: no character received 6 seconds.\r\n");
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */