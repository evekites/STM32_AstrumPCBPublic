/* USER CODE BEGIN PV */
int16_t readValue = 0;
int prevVal = 0;
int newVal;

int lookupTable[4][4] =
    {
        {0, -1, 1, 2},
        {1, 0, 2, -1},
        {-1, 2, 0, 1},
        {2, 1, -1, 0}};
int clockState = 0;
int counterClockState = 0;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
int valA = HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin);
int valB = HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin);
prevVal = (valA << 1) + valB;
/* USER CODE END 1 */

/* USER CODE BEGIN WHILE */
void Read_Rotary()
{
  int valA = HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin);
  int valB = HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin);
  newVal = (valA << 1) + valB;

  int info = lookupTable[prevVal][newVal];

  if (info == 1)
  {
    clockState |= (1 << newVal);
  }
  else if (info == -1)
  {
    counterClockState |= (1 << newVal);
  }
  else if (info == 2)
  {
    // skipped a value
  }

  if (prevVal != newVal && newVal == 3)
  {
    if (clockState == 0b1011 || clockState == 0b1101 || clockState == 0b1110 || clockState == 0b1111)
    {
      readValue++; // clockwise
      HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    }
    if (counterClockState == 0b1011 || counterClockState == 0b1101 || counterClockState == 0b1110 || counterClockState == 0b1111)
    {
      readValue--; // counterclockwise
      HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    }
    clockState = 0;
    counterClockState = 0;
  }
  prevVal = newVal;
  printf("De teller is: %d\r\n", readValue);
}

while (1)
{
  if (!HAL_GPIO_ReadPin(ROTARY_SWITCH_GPIO_Port, ROTARY_SWITCH_Pin))
  {
    readValue = 0;
  }
  Read_Rotary();
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */