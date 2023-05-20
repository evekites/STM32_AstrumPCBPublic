/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 1 */
HAL_StatusTypeDef ret;
uint8_t buf[1];
/* USER CODE END 1 */

/* USER CODE BEGIN WHILE */
static const uint8_t IO_EXT_READ = 0x21 << 1;		 // Use 8-bit address
static const uint8_t IO_EXT_WRITE = IO_EXT_READ + 1; // 1 higher then IO_EXT_READ
#define SW2 0b00000001
#define M_LED_RED 0b00000010
#define M_LED_GREEN 0b00000100
#define M_LED_BLUE 0b00001000
#define LED_BLUE 0b00010000
#define GPIO2A 0b00100000
#define GPIO2B 0b01000000
#define J1100_1 0b10000000

void LED_Off(int iRegisterValue, int iMask)
{
	bool highON = true;
	// The M_LEDs are OFF when high, so highON = false
	if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
		highON = false;
	if (highON)
	{
		buf[0] = iRegisterValue & ~iMask;
	}
	else // For the M_LEDs the logic is reversed, so ON when LOW and OFF when HIGH
	{
		buf[0] = iRegisterValue | iMask;
	}
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, buf, 1,
								  HAL_MAX_DELAY); // Write buf[0] to IO Extender
	if (ret != HAL_OK)
	{
		// I2C error
	}
}

void LED_On(int iRegisterValue, int iMask)
{
	bool highON = true;
	// The M_LEDs are OFF when high, so highON = false
	if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
		highON = false;
	if (highON)
	{
		buf[0] = iRegisterValue | iMask;
	}
	else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
	{
		buf[0] = iRegisterValue & ~iMask;
	}
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, buf, 1,
								  HAL_MAX_DELAY); // Write buf[0] to IO Extender
	if (ret != HAL_OK)
	{
		// I2C error
	}
}

void LEDs_On()
{
	LED_On(buf[0], M_LED_RED);
	LED_On(buf[0], M_LED_GREEN);
	LED_On(buf[0], M_LED_BLUE);
	LED_On(buf[0], LED_BLUE);
	LED_On(buf[0], GPIO2A);
	LED_On(buf[0], GPIO2B);
	LED_On(buf[0], J1100_1);
}

void LEDs_Off()
{
	LED_Off(buf[0], M_LED_RED);
	LED_Off(buf[0], M_LED_GREEN);
	LED_Off(buf[0], M_LED_BLUE);
	LED_Off(buf[0], LED_BLUE);
	LED_Off(buf[0], GPIO2A);
	LED_Off(buf[0], GPIO2B);
	LED_Off(buf[0], J1100_1);
}

void LED_Toggle(int iRegisterValue, int iMask)
{
	buf[0] = iRegisterValue ^ iMask;
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, buf, 1,
								  HAL_MAX_DELAY);
	if (ret != HAL_OK)
	{
		// I2C error
	}
}

LEDs_Off();

int LEDs[7] =
	{M_LED_RED, M_LED_GREEN, M_LED_BLUE, LED_BLUE, GPIO2A, GPIO2B, J1100_1};

while (1)
{
	ret = HAL_I2C_Master_Receive(&hi2c1, IO_EXT_READ, buf, 1,
								 HAL_MAX_DELAY); // Retrieve data from IO_Extender into buf[0]
	if (ret != HAL_OK)
	{
		// I2C error
	}
	int DELAY = 200;

	for (int LEDnr = 0; LEDnr < 7; LEDnr++)
	{
		LED_On(buf[0], LEDs[LEDnr]);
		HAL_Delay(DELAY);
		LED_Off(buf[0], LEDs[LEDnr]);
		HAL_Delay(DELAY);
	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
