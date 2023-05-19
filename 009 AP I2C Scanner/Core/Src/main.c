/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
uint8_t ret;

void LED_RED_Blink(int iTimes)
{
  for (int iCounter = 0; iCounter < iTimes; iCounter++)
  {
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    HAL_Delay(50);
  }
}

void I2C_scanner()
{
  LED_RED_Blink(1);
  printf("Scanresults I2C1\r\n");
  for (int i = 1; i < 128; i++)
  {
    ret = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i << 1), 3, 5);
    if (ret == HAL_OK)
    {
      printf("I2C1: 0x%X\r\n", i);
    }
  }
  printf("Scanresults I2C3\r\n");
  for (int i = 1; i < 128; i++)
  {
    ret = HAL_I2C_IsDeviceReady(&hi2c3, (uint16_t)(i << 1), 3, 5);
    if (ret == HAL_OK)
    {
      printf("I2C3: 0x%X\r\n", i);
    }
  }
  printf("\r\n");
  HAL_Delay(100);
  LED_RED_Blink(2);
}
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
HAL_Delay(2000);
printf("Press S1 to scan I2C1 & I2C3.\r\n");
while (1)
{
  if (!HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin))
  {
    I2C_scanner();
    printf("Press S1 to scan I2C1 & I2C3 again.\r\n");
  }
  HAL_Delay(100);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */