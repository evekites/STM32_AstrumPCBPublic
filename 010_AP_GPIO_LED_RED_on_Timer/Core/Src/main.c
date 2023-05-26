/* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim16);
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}
/* USER CODE END 4 */
