/* USER CODE BEGIN WHILE */
for (int iCounter = 0; iCounter < 5; iCounter++)
{
    HAL_GPIO_WritePin(BUZZER_GROVE_GPIO_Port, BUZZER_GROVE_Pin, GPIO_PIN_SET);
    HAL_Delay(25);
    HAL_GPIO_WritePin(BUZZER_GROVE_GPIO_Port, BUZZER_GROVE_Pin, GPIO_PIN_RESET);
    HAL_Delay(150);
}
while (1)
{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */