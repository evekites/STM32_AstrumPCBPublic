/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PFP */
void write_fc_data(char LGSE2, bool Poker, char BC, int CCR, int CCG, int CCB, char LGSE1, char SEL_SCK_EDGE, char LGSE3, char ESPWM, char SEL_PCHG, char SEL_GCK_EDGE,
                   char XREFRESH, char SEL_GDLY, char SEL_TD0, char LODVTH);
void gradient(void);
void write_gs_data(int *temp);
void write_gs_data_poker(int *temp);
void __delay_cycles(unsigned int cycles);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void pca9955b_set_IREFALL(const uint8_t gain)
{
  uint8_t data_ref[2] = {0x45, gain};
  HAL_I2C_Master_Transmit(&hi2c3, 0xD3, data_ref, 2, 500);
}

void pca9955b_set_PWMALL(const uint8_t brightness)
{
  uint8_t data_bright[2] = {0x44, brightness};
  HAL_I2C_Master_Transmit(&hi2c3, 0xD3, data_bright, 2, 500);
}

void pca9955b_set_PWM(const uint8_t led, const uint8_t brightness)
{
  uint8_t data_bright[2] = {0x08 + led, brightness};
  HAL_I2C_Master_Transmit(&hi2c3, 0xD3, data_bright, 2, 500);
}

void gs_set_pixel(int gs_data[], unsigned int pixel, int red, int green, int blue)
{
  unsigned int pixel_base_loc = pixel * 3;

  gs_data[pixel_base_loc] = red;
  gs_data[pixel_base_loc + 1] = green;
  gs_data[pixel_base_loc + 2] = blue;
}

void gs_set_all_pixels(int gs_data[], int red, int green, int blue)
{
  for (int i = 0; i < 16; i++)
    gs_set_pixel(gs_data, i, red, green, blue);
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
white_led_test_init();

pca9955b_set_IREFALL(255);
pca9955b_set_PWMALL(0);

write_fc_data(0, 1, 2, 256, 256, 256, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0);
gradient();

int gs_data[] = {
    0, 0, 0, // D0 R,G,B
    0, 0, 0, // D1 R,G,B
    0, 0, 0, // D2 R,G,B
    0, 0, 0, // D3 R,G,B
    0, 0, 0, // D4 R,G,B
    0, 0, 0, // D5 R,G,B
    0, 0, 0, // D6 R,G,B
    0, 0, 0, // D7 R,G,B
    0, 0, 0, // D8 R,G,B
    0, 0, 0, // D9 R,G,B
    0, 0, 0, // D10 R,G,B
    0, 0, 0, // D11 R,G,B
    0, 0, 0, // D12 R,G,B
    0, 0, 0, // D13 R,G,B
    0, 0, 0, // D14 R,G,B
    0, 0, 0, // D15 R,G,B
};
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1)
{
#if 1
  /* Fade in */
  for (int i = 0; i < 3000; i++)
  {
    gs_set_all_pixels(gs_data, i, i, i);
    write_gs_data_poker(gs_data);
    __delay_cycles(1000);
  }

  /* Fade out */
  for (int j = 3000; j > 0; j--)
  {
    gs_set_all_pixels(gs_data, j, j, j);
    write_gs_data_poker(gs_data);
    __delay_cycles(1000);
  }
#endif

#if 0
		for (int i = 0; i < 16; i++) {
			gs_set_all_pixels(gs_data, 0, 0, 0);
			gs_set_pixel(gs_data, i, 200, 200, 200);
			write_gs_data_poker(gs_data);
			__delay_cycles(250000);
		}
#endif

#if 0
		for (int i = 0; i < 16; i++) {
			pca9955b_set_PWMALL(0);
			pca9955b_set_PWM(i, 10);
			__delay_cycles(250000);
		}
#endif
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/* USER CODE BEGIN TIM2_Init 2 */
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
/* USER CODE END TIM2_Init 2 */

/* USER CODE BEGIN 4 */
void white_led_test_init(void)
{
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);   // gpio 5v ring
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);   // i2c reset pin High
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); // i2c oe Low
}

/**
 *
 * | signal | Pin | direction |
 * |  SIN   | PB5 | out       |
 * |  SCLK  | PA5 | out       |
 * |  LAT   | PA3 | out       |
 * | SOUT   | PA6 | in        |
 */
void Init_TLC5957(void)
{

  /* TODO */
  // SIN, SCLK, XLAT

  // SOUT
  // SCLK
}

void SIN(bool i)
{
  if (i)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

void SCLK(bool i)
{
  if (i)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void LAT(bool i)
{
  if (i)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

void GCLK(bool i)
{
  if (i)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}

void __delay_cycles(unsigned int cycles)
{
  for (volatile unsigned int i = 0; i < cycles; i++)
    continue;
}

/*FC Data Write Function*/
void write_fc_data(char LGSE2, bool Poker, char BC, int CCR, int CCG, int CCB, char LGSE1, char SEL_SCK_EDGE, char LGSE3, char ESPWM, char SEL_PCHG, char SEL_GCK_EDGE,
                   char XREFRESH, char SEL_GDLY, char SEL_TD0, char LODVTH)
{
  int k;
  char temp1, temp2;
  int temp3, temp4;
  LAT(0);
  LAT(1);

  /* FCWRTEN */
  for (k = 14; k >= 0; k--)
  {
    SIN(1); // SIN don't care
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }
  LAT(0);

  /* FC Data */
  for (k = 47; k >= 45; k--)
  {
    temp1 = 1 << (k - 45);
    temp2 = LGSE2 & temp1;
    if (temp2 == temp1)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* Poker trans mode  44th common shift register */
  if (Poker == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* BC Data */
  for (k = 43; k >= 41; k--)
  {
    temp1 = 1 << (k - 41);
    temp2 = BC & temp1;
    if (temp2 == temp1)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* CCR Data */
  for (k = 40; k >= 32; k--)
  {
    temp3 = 1 << (k - 32);
    temp4 = CCR & temp3;
    if (temp4 == temp3)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* CCG Data */
  for (k = 31; k >= 23; k--)
  {
    temp3 = 1 << (k - 23);
    temp4 = CCG & temp3;
    if (temp4 == temp3)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* CCB Data */
  for (k = 22; k >= 14; k--)
  {
    temp3 = 1 << (k - 14);
    temp4 = CCB & temp3;
    if (temp4 == temp3)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* LGSE1 Data */
  for (k = 13; k >= 11; k--)
  {
    temp1 = 1 << (k - 11);
    temp2 = LGSE1 & temp1;
    if (temp2 == temp1)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* SEL_SCK_EDGE */
  if (SEL_SCK_EDGE == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* LGSE3 */
  if (LGSE3 == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* ESPWM */
  if (ESPWM == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* SEL_PCHG */
  if (SEL_PCHG == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* SEL_GCK_EDGE */
  if (SEL_GCK_EDGE == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* XREFRESH */
  if (XREFRESH == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);
  /* WRTFC Command */
  LAT(1);
  /* SEL_GDLY */
  if (SEL_GDLY == 0)
    SIN(0);
  else
    SIN(1);
  SCLK(0);
  __delay_cycles(1); // 1/25M=40ns
  SCLK(1);

  /* SEL_TD0 */
  for (k = 3; k >= 2; k--)
  {
    temp1 = 1 << (k - 2);
    temp2 = SEL_TD0 & temp1;
    if (temp2 == temp1)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* LODVTH */
  for (k = 1; k >= 0; k--)
  {
    temp1 = 1 << k;
    temp2 = LODVTH & temp1;
    if (temp2 == temp1)
      SIN(1);
    else
      SIN(0);
    SCLK(0);
    __delay_cycles(1); // 1/25M=40ns
    SCLK(1);
  }

  /* WRTFC Command */
  LAT(0);
}

/*GS Data Write Function - Normal Mode - GPIO Driving*/
void write_gs_data(int *temp)
{
  int k, temp1, temp2;
  LAT(0); // Latch Low
  for (int i = 15; i >= 0; i--)
  {
    for (int j = 47; j >= 0; j--)
    {
      temp1 = 1 << (j % 16);
      temp2 = temp[i * 3 + j / 16] & temp1;
      if (temp2 == temp1)
        SIN(1); // SIN High
      else
        SIN(0); // SIN Low

      SCLK(0); // SCLK Low
      SCLK(1); // SCLK High

      k = i * 3 + j / 16;
      if (j == 3 && k == 0) // LATGS Command
        LAT(1);             // Latch High
      else if (j == 1)      // WRTGS Command
        LAT(1);             // Latch High
    }
    LAT(0); // Latch Low
  }
}

/* GS Data Write Function - Poker Mode - GPIO Driving*/
void write_gs_data_poker(int *temp)
{
  LAT(0);
  for (int i = 8; i >= 0; i--)
  {
    for (int j = 47; j >= 0; j--)
    {

      if ((temp[j] & (1 << i)) == (1 << i))
        SIN(1); // SIN High
      else
        SIN(0); // SIN Low

      SCLK(0); // SCLK Low
      SCLK(1); // SCLK High

      /* LATGS Command */
      if (j == 3 && i == 0)
        LAT(1); // Latch High
      /* WRTGS Command */
      else if (j == 1)
        LAT(1); // Latch High
    }
    LAT(0);
  }
}

void gradient(void)
{

  int GSdataL1[] = {
      25, 25, 25, // D0 R,G,B
      25, 25, 25, // D1 R,G,B
      25, 25, 25, // D2 R,G,B
      25, 25, 25, // D3 R,G,B
      25, 25, 25, // D4 R,G,B
      25, 25, 25, // D5 R,G,B
      25, 25, 25, // D6 R,G,B
      25, 25, 25, // D7 R,G,B
      25, 25, 25, // D8 R,G,B
      25, 25, 25, // D9 R,G,B
      25, 25, 25, // D10 R,G,B
      25, 25, 25, // D11 R,G,B
      25, 25, 25, // D12 R,G,B
      25, 25, 25, // D13 R,G,B
      25, 25, 25, // D14 R,G,B
      25, 25, 25, // D15 R,G,B
  };

  int GSdataL2[] = {
      50, 50, 50, // D0 R,G,B
      50, 50, 50, // D1 R,G,B
      50, 50, 50, // D2 R,G,B
      50, 50, 50, // D3 R,G,B
      50, 50, 50, // D4 R,G,B
      50, 50, 50, // D5 R,G,B
      50, 50, 50, // D6 R,G,B
      50, 50, 50, // D7 R,G,B
      50, 50, 50, // D8 R,G,B
      50, 50, 50, // D9 R,G,B
      50, 50, 50, // D10 R,G,B
      50, 50, 50, // D11 R,G,B
      50, 50, 50, // D12 R,G,B
      50, 50, 50, // D13 R,G,B
      50, 50, 50, // D14 R,G,B
      50, 50, 50, // D15 R,G,B
  };

  int GSdataL3[] = {
      75, 75, 75, // D0 R,G,B
      75, 75, 75, // D1 R,G,B
      75, 75, 75, // D2 R,G,B
      75, 75, 75, // D3 R,G,B
      75, 75, 75, // D4 R,G,B
      75, 75, 75, // D5 R,G,B
      75, 75, 75, // D6 R,G,B
      75, 75, 75, // D7 R,G,B
      75, 75, 75, // D8 R,G,B
      75, 75, 75, // D9 R,G,B
      75, 75, 75, // D10 R,G,B
      75, 75, 75, // D11 R,G,B
      75, 75, 75, // D12 R,G,B
      75, 75, 75, // D13 R,G,B
      75, 75, 75, // D14 R,G,B
      75, 75, 75, // D15 R,G,B
  };

  int GSdataL4[] = {
      100, 100, 100, // D0 R,G,B
      100, 100, 100, // D1 R,G,B
      100, 100, 100, // D2 R,G,B
      100, 100, 100, // D3 R,G,B
      100, 100, 100, // D4 R,G,B
      100, 100, 100, // D5 R,G,B
      100, 100, 100, // D6 R,G,B
      100, 100, 100, // D7 R,G,B
      100, 100, 100, // D8 R,G,B
      100, 100, 100, // D9 R,G,B
      100, 100, 100, // D10 R,G,B
      100, 100, 100, // D11 R,G,B
      100, 100, 100, // D12 R,G,B
      100, 100, 100, // D13 R,G,B
      100, 100, 100, // D14 R,G,B
      100, 100, 100, // D15 R,G,B
  };

  int GSdataL5[] = {
      125, 125, 125, // D0 R,G,B
      125, 125, 125, // D1 R,G,B
      125, 125, 125, // D2 R,G,B
      125, 125, 125, // D3 R,G,B
      125, 125, 125, // D4 R,G,B
      125, 125, 125, // D5 R,G,B
      125, 125, 125, // D6 R,G,B
      125, 125, 125, // D7 R,G,B
      125, 125, 125, // D8 R,G,B
      125, 125, 125, // D9 R,G,B
      125, 125, 125, // D10 R,G,B
      125, 125, 125, // D11 R,G,B
      125, 125, 125, // D12 R,G,B
      125, 125, 125, // D13 R,G,B
      125, 125, 125, // D14 R,G,B
      125, 125, 125, // D15 R,G,B
  };

  int GSdataL6[] = {
      150, 150, 150, // D0 R,G,B
      150, 150, 150, // D1 R,G,B
      150, 150, 150, // D2 R,G,B
      150, 150, 150, // D3 R,G,B
      150, 150, 150, // D4 R,G,B
      150, 150, 150, // D5 R,G,B
      150, 150, 150, // D6 R,G,B
      150, 150, 150, // D7 R,G,B
      150, 150, 150, // D8 R,G,B
      150, 150, 150, // D9 R,G,B
      150, 150, 150, // D10 R,G,B
      150, 150, 150, // D11 R,G,B
      150, 150, 150, // D12 R,G,B
      150, 150, 150, // D13 R,G,B
      150, 150, 150, // D14 R,G,B
      150, 150, 150, // D15 R,G,B
  };

  int GSdataL7[] = {
      175, 175, 175, // D0 R,G,B
      175, 175, 175, // D1 R,G,B
      175, 175, 175, // D2 R,G,B
      175, 175, 175, // D3 R,G,B
      175, 175, 175, // D4 R,G,B
      175, 175, 175, // D5 R,G,B
      175, 175, 175, // D6 R,G,B
      175, 175, 175, // D7 R,G,B
      175, 175, 175, // D8 R,G,B
      175, 175, 175, // D9 R,G,B
      175, 175, 175, // D10 R,G,B
      175, 175, 175, // D11 R,G,B
      175, 175, 175, // D12 R,G,B
      175, 175, 175, // D13 R,G,B
      175, 175, 175, // D14 R,G,B
      175, 175, 175, // D15 R,G,B
  };

  int GSdataL8[] = {
      200, 200, 200, // D0 R,G,B
      200, 200, 200, // D1 R,G,B
      200, 200, 200, // D2 R,G,B
      200, 200, 200, // D3 R,G,B
      200, 200, 200, // D4 R,G,B
      200, 200, 200, // D5 R,G,B
      200, 200, 200, // D6 R,G,B
      200, 200, 200, // D7 R,G,B
      200, 200, 200, // D8 R,G,B
      200, 200, 200, // D9 R,G,B
      200, 200, 200, // D10 R,G,B
      200, 200, 200, // D11 R,G,B
      200, 200, 200, // D12 R,G,B
      200, 200, 200, // D13 R,G,B
      200, 200, 200, // D14 R,G,B
      200, 200, 200, // D15 R,G,B
  };

  int GSdataL9[] = {
      225, 225, 225, // D0 R,G,B
      225, 225, 225, // D1 R,G,B
      225, 225, 225, // D2 R,G,B
      225, 225, 225, // D3 R,G,B
      225, 225, 225, // D4 R,G,B
      225, 225, 225, // D5 R,G,B
      225, 225, 225, // D6 R,G,B
      225, 225, 225, // D7 R,G,B
      225, 225, 225, // D8 R,G,B
      225, 225, 225, // D9 R,G,B
      225, 225, 225, // D10 R,G,B
      225, 225, 225, // D11 R,G,B
      225, 225, 225, // D12 R,G,B
      225, 225, 225, // D13 R,G,B
      225, 225, 225, // D14 R,G,B
      225, 225, 225, // D15 R,G,B
  };

  int GSdataL10[] = {
      250, 250, 250, // D0 R,G,B
      250, 250, 250, // D1 R,G,B
      250, 250, 250, // D2 R,G,B
      250, 250, 250, // D3 R,G,B
      250, 250, 250, // D4 R,G,B
      250, 250, 250, // D5 R,G,B
      250, 250, 250, // D6 R,G,B
      250, 250, 250, // D7 R,G,B
      250, 250, 250, // D8 R,G,B
      250, 250, 250, // D9 R,G,B
      250, 250, 250, // D10 R,G,B
      250, 250, 250, // D11 R,G,B
      250, 250, 250, // D12 R,G,B
      250, 250, 250, // D13 R,G,B
      250, 250, 250, // D14 R,G,B
      250, 250, 250, // D15 R,G,B
  };

  for (int i = 0; i < 30; i++)
  {
    write_gs_data_poker(GSdataL1);

    write_gs_data_poker(GSdataL2);

    write_gs_data_poker(GSdataL3);

    write_gs_data_poker(GSdataL4);

    write_gs_data_poker(GSdataL5);

    write_gs_data_poker(GSdataL6);

    write_gs_data_poker(GSdataL7);

    write_gs_data_poker(GSdataL8);

    write_gs_data_poker(GSdataL9);

    write_gs_data_poker(GSdataL10);
  }
}
/* USER CODE END 4 */