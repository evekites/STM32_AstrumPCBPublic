/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "ssd1306.h"
/* USER CODE END Includes */

/* USER CODE BEGIN WHILE */
while (1)
{
  SSD1306_Init();
  SSD1306_GotoXY(0, 0);
  SSD1306_Puts("STM32", &Font_11x18, 1);
  SSD1306_GotoXY(0, 20);
  SSD1306_Puts("demo", &Font_11x18, 1);
  SSD1306_UpdateScreen();
  HAL_Delay(1000);

  SSD1306_ScrollRight(0, 7);
  HAL_Delay(3000);
  SSD1306_ScrollLeft(0, 7);
  HAL_Delay(3000);
  SSD1306_Stopscroll();
  SSD1306_Clear();

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */