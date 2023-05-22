/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}

/* USER CODE END 0 */

/* USER CODE BEGIN WHILE */
while (1)
{
  for (int iCounter = 0; iCounter < 9999; iCounter++)
  {
    printf("iCounter: %d", iCounter);
    HAL_Delay(100);
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */