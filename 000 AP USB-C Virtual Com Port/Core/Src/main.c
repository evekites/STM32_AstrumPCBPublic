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
  for (int iCounter; iCounter < 1000; iCounter++)
  {
    printf("Counter: %d\r\n", iCounter);
    HAL_Delay(100);
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */