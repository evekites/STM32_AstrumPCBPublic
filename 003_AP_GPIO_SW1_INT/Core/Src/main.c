/* USER CODE BEGIN PV */
int SW1_ISR = 0;
/* USER CODE END PV */

/* USER CODE BEGIN WHILE */
while (1)
{
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  if (SW1_ISR == 1)
  {
    SW1_ISR = 0;
    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
  }
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == SW1_INT_Pin)
  {
    SW1_ISR = 1;
  }
}
/* USER CODE END 4 */
