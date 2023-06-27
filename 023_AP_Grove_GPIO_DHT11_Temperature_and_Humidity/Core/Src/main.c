/* USER CODE BEGIN 0 */
uint8_t RHI, RHD, TCI, TCD, SUM;
uint32_t pMillis, cMillis;
float tCelsius = 0;
float tFahrenheit = 0;
float RH = 0;

int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}

void microDelay(uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < delay)
    ;
}

uint8_t DHT11_Start(void)
{
  uint8_t Response = 0;
  GPIO_InitTypeDef GPIO_InitStructPrivate =
      {0};
  GPIO_InitStructPrivate.Pin = DHT11_Pin;
  GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStructPrivate); // set the pin as output
  HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 0);        // pull the pin low
  HAL_Delay(20);                                           // wait for 20ms
  HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 1);        // pull the pin high
  microDelay(30);                                          // wait for 30us
  GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStructPrivate); // set the pin as input
  microDelay(40);
  if (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)))
  {
    microDelay(80);
    if ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)))
      Response = 1;
  }
  pMillis = HAL_GetTick();
  cMillis = HAL_GetTick();
  while ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) && pMillis + 2 > cMillis)
  {
    cMillis = HAL_GetTick();
  }
  return Response;
}

uint8_t DHT11_Read(void)
{
  uint8_t a, b;
  for (a = 0; a < 8; a++)
  {
    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) && pMillis + 2 > cMillis)
    { // wait for the pin to go high
      cMillis = HAL_GetTick();
    }
    microDelay(40);                                      // wait for 40 us
    if (!(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))) // if the pin is low
      b &= ~(1 << (7 - a));
    else
      b |= (1 << (7 - a));
    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while ((HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) && pMillis + 2 > cMillis)
    { // wait for the pin to go low
      cMillis = HAL_GetTick();
    }
  }
  return b;
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
HAL_TIM_Base_Start(&htim1);
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
// x
while (1)
{
  if (DHT11_Start())
  {
    RHI = DHT11_Read(); // Relative humidity integral
    RHD = DHT11_Read(); // Relative humidity decimal
    TCI = DHT11_Read(); // Celsius integral
    TCD = DHT11_Read(); // Celsius decimal
    SUM = DHT11_Read(); // Check sum
    if (RHI + RHD + TCI + TCD == SUM)
    {
      // Can use RHI and TCI for any purposes if whole number only needed
      tCelsius = (float)TCI + (float)(TCD / 10.0);
      tFahrenheit = tCelsius * 9 / 5 + 32;
      RH = (float)RHI + (float)(RHD / 10.0);
      printf("Celsius: %f,  Humidity: %f\r\n", tCelsius, RH);
      // Can use tCelsius, tFahrenheit and RH for any purposes
    }
    if (TCI < 15)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
    }
    else if (TCI < 25)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
    }
  }
  HAL_Delay(2000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */