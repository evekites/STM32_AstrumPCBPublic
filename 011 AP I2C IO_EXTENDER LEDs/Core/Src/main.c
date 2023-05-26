/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 1 */
HAL_StatusTypeDef ret;
uint8_t I2CRegistervalues[1];
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

void LED_Off(int iMask)
{
	bool highON = true;
	// The M_LEDs are OFF when high, so highON = false
	if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
		highON = false;
	if (highON)
	{
		I2CRegistervalues[0] = I2CRegistervalues[0] & ~iMask;
	}
	else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
	{
		I2CRegistervalues[0] = I2CRegistervalues[0] | iMask;
	}
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
								  HAL_MAX_DELAY); // Write I2CRegistervalues[0] to IO Extender
	if (ret != HAL_OK)
	{
		printf("I2C error\r\n");
	}
}

void LED_On(int iMask)
{
	bool highON = true;
	// The M_LEDs are OFF when high, so highON = false
	if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
		highON = false;
	if (highON)
	{
		I2CRegistervalues[0] = I2CRegistervalues[0] | iMask;
	}
	else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
	{
		I2CRegistervalues[0] = I2CRegistervalues[0] & ~iMask;
	}
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
								  HAL_MAX_DELAY); // Write buf[0] to IO Extender
	if (ret != HAL_OK)
	{
		printf("I2C error\r\n");
	}
}

void LEDs_On()
{
	LED_On(M_LED_RED);
	LED_On(M_LED_GREEN);
	LED_On(M_LED_BLUE);
	LED_On(LED_BLUE);
	LED_On(GPIO2A);
	LED_On(GPIO2B);
	LED_On(J1100_1);
}

void LEDs_Off()
{
	LED_Off(M_LED_RED);
	LED_Off(M_LED_GREEN);
	LED_Off(M_LED_BLUE);
	LED_Off(LED_BLUE);
	LED_Off(GPIO2A);
	LED_Off(GPIO2B);
	LED_Off(J1100_1);
}

void LED_Toggle(int iMask)
{
	I2CRegistervalues[0] = I2CRegistervalues[0] ^ iMask;
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
								  HAL_MAX_DELAY);
	if (ret != HAL_OK)
	{
		printf("I2C error\r\n");
	}
}

LEDs_Off();

int LEDs[7] = {M_LED_RED, M_LED_GREEN, M_LED_BLUE, LED_BLUE, GPIO2A,
			   GPIO2B, J1100_1};

while (1)
{
	ret = HAL_I2C_Master_Receive(&hi2c1, IO_EXT_READ, I2CRegistervalues, 1,
								 HAL_MAX_DELAY); // Retrieve data from IO_Extender into buf[0]
	if (ret != HAL_OK)
	{
		// I2C error
	}
	int DELAY = 200;

	for (int LEDnr = 0; LEDnr < 7; LEDnr++)
	{
		LED_On(LEDs[LEDnr]);
		HAL_Delay(DELAY);
		LED_Off(LEDs[LEDnr]);
		HAL_Delay(DELAY);
	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */