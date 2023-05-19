/* USER CODE BEGIN 2 */
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

GPIO_PinState ROTARY_SWITCH_status()
{
    return HAL_GPIO_ReadPin(ROTARY_SWITCH_GPIO_Port, ROTARY_SWITCH_Pin);
}
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1)
{
#if 1
    LED_RED_set(!ROTARY_SWITCH_status());
#else
    if (!ROTARY_SWITCH_status())
    {
        LED_RED_on();
    }
    else
    {
        LED_RED_off();
    }
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
