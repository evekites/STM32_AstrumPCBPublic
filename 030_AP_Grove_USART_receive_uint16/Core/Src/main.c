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
  uint8_t buf[2];
  if (HAL_UART_Receive(&huart1, buf, 2, 6000) == HAL_OK) // haal 1 character
  {
    uint8_t iTellerMSB = buf[1];
    uint8_t iTellerLSB = buf[0];
    uint16_t iTeller = (iTellerMSB << 8) + iTellerLSB;
    printf("Nr-%d: MSB: %d, LSB: %d, iTeller: %d\r\n", iCounter, iTellerMSB, iTellerLSB, iTeller);
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