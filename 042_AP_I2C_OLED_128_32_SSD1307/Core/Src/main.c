/* USER CODE BEGIN Includes */
#include <string.h>
#include "fonts.h"
#include "ssd1307.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PD */
#define DISPLAY0 hi2c1

#define T_PIXEL_FILL_ANIMATION_ms 3000
#define T_TEXT_SCROLL_ANIMATION_ms 3000

#define Oled_TotalPixels SSD1307_HEIGHT *SSD1307_WIDTH

#define UART_BUFFER_SIZE 128
/* USER CODE END PD */

/* USER CODE BEGIN PV */
StaticCircularBuffer_t *pUartRxBuffer;
uint32_t millis = 0;
static uint8_t rxBuffer = 0;
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
long map(long x, long in_min, long in_max, long out_min, long out_max);
void SSD1307_animation_fill_square(I2C_HandleTypeDef *_hdisplay,
                                   uint32_t duration, uint8_t color, uint16_t width, uint16_t heigth);
void SSD1307_animation_scroll_window(I2C_HandleTypeDef *_hdisplay, char *text,
                                     uint32_t duration, uint8_t color, uint16_t height);
void SSD1307_animation_scroll_text(I2C_HandleTypeDef *_hdisplay, char *text,
                                   uint32_t duration, uint8_t color, uint16_t height);

void SSD1307_animation_interactive_adc_bar(I2C_HandleTypeDef *_hdisplay,
                                           uint32_t duration, uint8_t color);
void SSD1307_println(I2C_HandleTypeDef *_hdisplay, char *string, uint8_t color);

/* USER CODE END PFP */

/* USER CODE BEGIN 2 */
if (ssd1307_Init(&DISPLAY0, 0))
    Error_Handler();
for (int i = 0; i < 4000000; i++)
{
    __asm("nop");
}

SSD1307_println(&DISPLAY0, "Gemini-et.nl", Black);
SSD1307_println(&DISPLAY0, "", Black);

HAL_Delay(2000);
/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1)
{
    SSD1307_animation_fill_square(&DISPLAY0, T_PIXEL_FILL_ANIMATION_ms,
                                  White, SSD1307_WIDTH, SSD1307_HEIGHT);
    SSD1307_animation_scroll_text(&DISPLAY0, "Hello Gemini", 5000, White,
                                  SSD1307_HEIGHT / 2 - (Font_7x10.FontHeight / 2));
    HAL_Delay(4000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void SSD1307_animation_fill_square(I2C_HandleTypeDef *_hdisplay,
                                   uint32_t duration, uint8_t color, uint16_t width, uint16_t heigth)
{
    uint32_t t_start_pixelFillAnimation = 0;
    uint32_t pixel_count = 0;

    // fill animation connected to time.
    for (int y = 0; y < heigth; y++)
    {
        // save start time
        if (!t_start_pixelFillAnimation)
            t_start_pixelFillAnimation = millis;

        for (int x = 0; x < width; x++)
        {
            ssd1307_DrawPixel(x, y, color);

            /*slow animation down then pixels are filling too fast by updating screen which takes a significant amount of time*/
            if (pixel_count > (((double)(width * heigth) / (double)duration) * (millis - t_start_pixelFillAnimation)) || (x == (width - 1) && y == (heigth - 1)))
            {
                ssd1307_UpdateScreen(_hdisplay);
            }
            pixel_count++;
        }
    }
    t_start_pixelFillAnimation = 0;
    pixel_count = 0;
}

void SSD1307_animation_scroll_window(I2C_HandleTypeDef *_hdisplay, char text[],
                                     uint32_t duration, uint8_t color, uint16_t height)
{
    uint32_t t_start_textScrollAnimation = 0;

    // scroll text
    for (int i = 0; i < SSD1307_WIDTH; i++)
    {
        if (!t_start_textScrollAnimation)
            t_start_textScrollAnimation = millis;
        ssd1307_Fill(!color);
        ssd1307_SetCursor(i, height);
        ssd1307_WriteString(text, Font_7x10, color);

        /*slow animation down then pixels are filling too fast by updating screen which takes a significant amount of time*/
        if (i > (((double)SSD1307_WIDTH / (double)duration) * (millis - t_start_textScrollAnimation)) || (i == (SSD1307_WIDTH - 1)))
        {
            ssd1307_UpdateScreen(_hdisplay);
        }
    }
    t_start_textScrollAnimation = 0;

    ssd1307_Fill(!color);
    ssd1307_UpdateScreen(&hi2c1);
}

void SSD1307_animation_scroll_text(I2C_HandleTypeDef *_hdisplay, char *text,
                                   uint32_t duration, uint8_t color, uint16_t height)
{
    uint32_t t_start_textScrollAnimation = millis;
    char buffer[500];
    strcpy(buffer, "");

    // calculate and create padding in front of string
    for (int i = 0; i < (SSD1307_WIDTH / Font_7x10.FontWidth); i++)
    {
        strcat(buffer, " ");
    }

    // add text in buffer
    strcat(buffer, text);

    int len = strlen(buffer);

    for (int i = 0; i < len; i++)
    {
        ssd1307_Fill(!color);
        ssd1307_SetCursor(0, height);
        ssd1307_WriteString(&buffer[i], Font_7x10, color);
        ssd1307_UpdateScreen(_hdisplay);
        // delay
        while (i > (((double)len / ((double)duration)) * (millis - t_start_textScrollAnimation)))
            ;
    }
    t_start_textScrollAnimation = 0;

    ssd1307_Fill(!color);
    ssd1307_UpdateScreen(_hdisplay);
}

/**
 * \brief function to print a line of text to display
 *
 * this function prints a line and the previous printed lines on the display,
 * mimicking a console.
 *
 * \param _hdisplay the i2c handler for the display
 * \param string a pointer to the string that need to get printed
 * \param color the color of the string, the background will be the opposite color
 */
void SSD1307_println(I2C_HandleTypeDef *_hdisplay, char *string, uint8_t color)
{
    FontDef font = Font_7x10;
    const int line_amount = (int)floor(
        (float)SSD1307_HEIGHT / (float)font.FontHeight);

    static char screen_text_buffer[10][SSD1307_WIDTH] =
        {""};
    static uint8_t line = 0; // line number that the current 'console' is at

    if (line >= line_amount)
    {
        line--;

        // move all lines up one line, discarding ones going out of bound
        for (int i = 0; i < line_amount - 1; i++)
        {
            strcpy(screen_text_buffer[i], screen_text_buffer[i + 1]);
        }
    }

    // write string
    if (strlen(string) < 128)
    {
        strcpy(screen_text_buffer[line], string);
    }
    else
    {
        strcpy(screen_text_buffer[line], "Size ERROR");
    }

    ssd1307_Fill(!color);
    for (int i = 0; i < line_amount; i++)
    {
        ssd1307_SetCursor(0, (font.FontHeight) * i);
        ssd1307_WriteString(screen_text_buffer[i], font, color);
    }

    line++;
    ssd1307_UpdateScreen(&DISPLAY0);
}

/* USER CODE END 4 */