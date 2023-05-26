/* USER CODE BEGIN 2 */
#define TIME_ON 1000
#define TIME_OFF 500
void LED_RED_on()
{
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
}

void LED_RED_off()
{
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
}

void LED_RED_set(GPIO_PinState LED_Status)
{
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, LED_Status);
}
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1)
{
  LED_RED_on();
  HAL_Delay(TIME_ON);
  LED_RED_off();
  HAL_Delay(TIME_OFF);
  LED_RED_set(GPIO_PIN_SET);
  HAL_Delay(TIME_ON);
  LED_RED_set(GPIO_PIN_RESET);
  HAL_Delay(TIME_OFF);

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */