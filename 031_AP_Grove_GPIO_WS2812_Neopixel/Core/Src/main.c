/* USER CODE BEGIN 0 */
#define WS2812_LED_MAX 10
uint8_t LED_Data[WS2812_LED_MAX][4];
int datasentflag = 0;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
  datasentflag = 1;
}

void ws2812_Set_LED(int LEDnum, int Red, int Green, int Blue)
{
  LED_Data[LEDnum][0] = LEDnum;
  LED_Data[LEDnum][1] = Green;
  LED_Data[LEDnum][2] = Red;
  LED_Data[LEDnum][3] = Blue;
}

void ws2812_SetAll_LED(int Red, int Green, int Blue)
{
  for (int i = 0; i < WS2812_LED_MAX; i++)
  {
    ws2812_Set_LED(i, Red, Green, Blue);
  }
}

void ws2812_Send_PWM(void)
{
  uint16_t pwmData[24 * (WS2812_LED_MAX) + 50];
  uint32_t indx = 0;
  uint32_t color;
  for (int i = 0; i < WS2812_LED_MAX; i++)
  {
    color = ((LED_Data[i][1] << 16) | (LED_Data[i][2] << 8) | (LED_Data[i][3]));
    for (int i = 23; i >= 0; i--)
    {
      if (color & (1 << i))
      {
        pwmData[indx] = 50; // 2/3 of ARR=75
      }

      else
        pwmData[indx] = 25; // 1/3 of ARR=75

      indx++;
    }
  }
  for (int i = 0; i < 50; i++)
  {
    pwmData[indx] = 0;
    indx++;
  }
  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)pwmData, indx);
  while (!datasentflag)
  {
  };
  datasentflag = 0;
}

/* USER CODE END 0 */

/* USER CODE BEGIN WHILE */
ws2812_SetAll_LED(0, 0, 0);
for (int i = 0; i < WS2812_LED_MAX; i++)
{
  ws2812_Set_LED(i, 30, 30, 30);
  ws2812_Send_PWM();
  HAL_Delay(500);
}

while (1)
{
  ws2812_SetAll_LED(30, 0, 0);
  ws2812_Send_PWM();
  HAL_Delay(1000);
  ws2812_SetAll_LED(30, 63, 0);
  ws2812_Send_PWM();
  HAL_Delay(1000);

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */