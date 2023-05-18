/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN WHILE */
BMP280_init();
HAL_Delay(1000);
printf("BMP280\r\n");
extern float temperature, pressure, altitude, init_height;
BMP280_calc_values();

init_height = altitude;

while (1)
{
  BMP280_calc_values();
  printf("Temp: %05.1f, Pressure: %.0f, Altitude: %.2f\r\n", temperature,
         pressure, altitude - init_height);
  if (temperature > 27)
  {
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
  }
  HAL_Delay(1000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
