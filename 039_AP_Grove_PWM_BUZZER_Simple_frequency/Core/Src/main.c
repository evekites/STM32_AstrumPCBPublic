/* USER CODE BEGIN WHILE */
int x;
for (x = 10; x < 128; x++)
{
    __HAL_TIM_SET_AUTORELOAD(&htim1, x * 2);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, x);
    HAL_Delay(30);
}
__HAL_TIM_SET_AUTORELOAD(&htim1, 1 * 2);
__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1);

while (1)
{
/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */