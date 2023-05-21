/* USER CODE BEGIN 0 */
volatile uint8_t displayColon = 0;
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
TM1637_SetBrightness(7);
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1)
{
  for (int var = 0; var < 9999; var++)
  {
    displayColon = !displayColon;
    TM1637_DisplayDecimal(var, displayColon);
    // HAL_Delay(1);
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */