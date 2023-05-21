/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
static const uint8_t IO_EXT_READ = 0x21 << 1;		 // Use 8-bit address
static const uint8_t IO_EXT_WRITE = IO_EXT_READ + 1; // Use 8-bit address
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

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
	((byte)&0x80 ? '1' : '0'),     \
		((byte)&0x40 ? '1' : '0'), \
		((byte)&0x20 ? '1' : '0'), \
		((byte)&0x10 ? '1' : '0'), \
		((byte)&0x08 ? '1' : '0'), \
		((byte)&0x04 ? '1' : '0'), \
		((byte)&0x02 ? '1' : '0'), \
		((byte)&0x01 ? '1' : '0')

bool CheckPin(int iMask)
{
	ret = HAL_I2C_Master_Receive(&hi2c1, IO_EXT_READ, buf, 1,
								 HAL_MAX_DELAY); // Retreive data from IO_Extender into buf[0]
	if (ret != HAL_OK)
	{
		printf("I2C error\r\n");
	}
	printf("Buffer " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(buf[0]));
	printf(" mask " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(iMask));
	printf(" ");
	if ((buf[0] & iMask) == iMask)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
	else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
	{
		buf[0] = iRegisterValue | iMask;
	}
	ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, buf, 1,
								  HAL_MAX_DELAY); // Write buf[0] to IO Extender
	if (ret != HAL_OK)
	{
		printf("I2C error\r\n");
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
		printf("I2C error\r\n");
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
		printf("I2C error\r\n");
	}
}

LEDs_Off();
int LEDnr = 0;
int LEDs[8] =
	{M_LED_RED, M_LED_GREEN, M_LED_BLUE, LED_BLUE}; // enough room to use LED's on GPIO2A, GPIO2B & J1100_1

while (1)
{
#define SWITCH GPIO2A
#if SWITCH == SW2
	if (!CheckPin(SW2))
#elif SWITCH == GPIO2A
	if (CheckPin(GPIO2A))
#elif SWITCH == GPIO2B
	if (CheckPin(GPIO2B))
#elif SWITCH == J1100_1
	if (CheckPin(J1100_1))
#endif
	{
		LEDnr++;
		if (LEDnr >= 4)
			LEDnr = 0;
		printf("HIGH\r\n");
		LED_Toggle(buf[0], LEDs[LEDnr]);
		HAL_Delay(200);

		// LEDs_On();
	}
	else
	{
		printf("LOW\r\n");
		LEDs_Off();
	}

	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
