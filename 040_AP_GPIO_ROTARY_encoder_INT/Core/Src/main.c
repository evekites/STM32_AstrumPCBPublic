/* USER CODE BEGIN PV */
static int8_t states[] =
    {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
uint8_t RotaryCurrentState = 0x00;
uint8_t RotaryTransition = 0;
int8_t RotaryPosition = 0;
int iTeller = 0;

/*
 Rotary Encoder Interrupt Handler
 Channel A (IRQ12) & B (IRQ11)

 CW --->
 A (IRQ12)  ¯|___|¯¯¯¯|___|¯¯¯¯
 Interrupts  ^   ^    ^   ^
 B (IRQ 11) ¯¯¯|___|¯¯¯¯¯|___|¯
 Interrupts    ^   ^     ^   ^
 CCW <---
 */
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN WHILE */
RotaryTransition = HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin) << 3 | HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin) << 2 | HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin) << 1 | HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin);
int iPreviousTeller = iTeller;
while (1)
{
  if (iPreviousTeller != iTeller)
  {
    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    iPreviousTeller = iTeller;
    printf("Teller: %d", iTeller);
    HAL_Delay(100);
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  RotaryCurrentState = (HAL_GPIO_ReadPin(ROTARY1_GPIO_Port, ROTARY1_Pin) << 1) | HAL_GPIO_ReadPin(ROTARY2_GPIO_Port, ROTARY2_Pin);
  RotaryTransition = (RotaryTransition << 2) | RotaryCurrentState;
  RotaryPosition = RotaryPosition + states[RotaryTransition & 0x0F];
  if (RotaryPosition == 4)
  {
    iTeller++;
    RotaryPosition = 0;
  }
  if (RotaryPosition == -4)
  {
    iTeller--;
    RotaryPosition = 0;
  }
}
/* USER CODE END 4 */