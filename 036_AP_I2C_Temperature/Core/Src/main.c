/* USER CODE BEGIN PV */
static const uint8_t TEMP_READ = 0x4C << 1;      // Use 8-bit address
static const uint8_t TEMP_WRITE = TEMP_READ + 1; // Use 8-bit address
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
void ReadTemp()
{
  buf[0] = 0x00; // register for reading temperature = 0x00
  ret = HAL_I2C_Master_Transmit(&hi2c1, TEMP_WRITE, buf, 1,
                                HAL_MAX_DELAY);
  if (ret != HAL_OK)
  {
    printf("I2C error\r\n");
  }

  // temperature is stored in 2 bytes, left 8 bits is temp as integer
  // left 11 bits gives temp as float (last 5 bytes are ignored =0)
  ret = HAL_I2C_Master_Receive(&hi2c1, TEMP_READ, buf, 2,
                               HAL_MAX_DELAY);
  if (ret != HAL_OK)
  {
    printf("I2C error\r\n");
  }
  float temperature = (buf[1] >> 5) * 0.125 + buf[0];
  printf(" %f", temperature);
  printf("\r\n");
}

while (1)
{
  ReadTemp();
  HAL_Delay(1000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */