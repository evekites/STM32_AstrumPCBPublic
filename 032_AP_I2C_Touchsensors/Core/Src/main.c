/* USER CODE BEGIN PV */
static const uint8_t TOUCH_READ = 0x28 << 1;       // Use 8-bit address
static const uint8_t TOUCH_WRITE = TOUCH_READ + 1; // Use 8-bit address

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)     \
  ((byte)&0x80 ? '1' : '0'),     \
      ((byte)&0x40 ? '1' : '0'), \
      ((byte)&0x20 ? '1' : '0'), \
      ((byte)&0x10 ? '1' : '0'), \
      ((byte)&0x08 ? '1' : '0'), \
      ((byte)&0x04 ? '1' : '0'), \
      ((byte)&0x02 ? '1' : '0'), \
      ((byte)&0x01 ? '1' : '0')

/* USER CODE END PV */

/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  CDC_Transmit_FS((uint8_t *)ptr, len);
  return len;
}
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
HAL_StatusTypeDef ret;
uint8_t buf[2];
/* USER CODE END 1 */

/* USER CODE BEGIN WHILE */
void Touch_check()
{
  buf[0] = 0x03;
  ret = HAL_I2C_Master_Transmit(&hi2c3, TOUCH_WRITE, buf, 1,
                                HAL_MAX_DELAY);
  if (ret != HAL_OK)
  {
    printf("I2C error\r\n");
  }

  ret = HAL_I2C_Master_Receive(&hi2c3, TOUCH_READ, buf, 2,
                               HAL_MAX_DELAY); // Retreive data from IO_Extender into buf[0]
  if (ret != HAL_OK)
  {
    printf("I2C error\r\n");
  }
  printf(" 03h " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(buf[0]));
  if (buf[0] > 0)
  {
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
  }
  printf("\r\n");
}

void Touch_clear()
{
  buf[0] = 0x00;
  buf[1] = 0x00;
  ret = HAL_I2C_Master_Transmit(&hi2c3, TOUCH_WRITE, buf, 2,
                                HAL_MAX_DELAY);
  if (ret != HAL_OK)
  {
    printf("I2C error\r\n");
  }
}

while (1)
{
  if (!HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin))
  {
    Touch_clear();
  }
  Touch_check();
  HAL_Delay(100);

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */