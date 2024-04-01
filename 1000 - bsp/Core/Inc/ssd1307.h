/**
 * This Library is written and optimized by Olivier Van den Eede(4ilo) in 2016
 * for Stm32 Uc and HAL-i2c lib's.
 *
 * To use this library with ssd1307 oled display you will need to customize the defines below.
 *
 * This library uses 2 extra files (fonts.c/h).
 * In this files are 3 different fonts you can use:
 *     - Font_7x10
 *     - Font_11x18
 *     - Font_16x26
 *
 */

#ifndef _SSD1307_H
#define _SSD1307_H

#include "stm32wbxx_hal.h"
#include "fonts.h"

#include <math.h>
#include <string.h>
//#include "fonts.h"

#ifndef SSD1307_I2C_ADDR
#define SSD1307_I2C_ADDR        0x78
#endif // SSD1307_I2C_ADDR

// SSD1307 width in pixels
#ifndef SSD1307_WIDTH
#define SSD1307_WIDTH           128ul
#endif // SSD1307_WIDTH

// SSD1307 LCD height in pixels
#ifndef SSD1307_HEIGHT
#define SSD1307_HEIGHT          32ul
#endif // SSD1307_HEIGHT

#ifndef SSD1307_COM_LR_REMAP
#define SSD1307_COM_LR_REMAP    0
#endif // SSD1307_COM_LR_REMAP

#ifndef SSD1307_COM_ALTERNATIVE_PIN_CONFIG
#define SSD1307_COM_ALTERNATIVE_PIN_CONFIG    1
#endif // SSD1307_COM_ALTERNATIVE_PIN_CONFIG

#define F_CPU 64000000UL

#define DISPLAY0 hi2c1

#define LPTIM1_ARR_MATCH_PERIOD_ms (1u) //ms
#define LPTIM_FCLK (64000000ul)
#define LPTIM_PSC (8u)

#define LPTIM1_ARR_MATCH_FRECUENCY (1000ul/LPTIM1_ARR_MATCH_PERIOD_ms)
#define LPTIM1_ARR ((LPTIM_FCLK/(LPTIM_PSC*LPTIM1_ARR_MATCH_FRECUENCY))-1)
#define Oled_TotalPixels SSD1307_HEIGHT * SSD1307_WIDTH

#define TAB_SIZE 4

//
//  Enumeration for screen colors
//
typedef enum {
    Black = 0x00,   // Black color, no pixel
    White = 0x01,   // Pixel is set. Color depends on LCD
} SSD1307_COLOR;

//
//  Struct to store transformations
//
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1307_t;

uint8_t ssd1307_Init(I2C_HandleTypeDef *hi2c, uint8_t orientation);
void ssd1307_UpdateScreen(I2C_HandleTypeDef *hi2c);
void ssd1307_Fill(SSD1307_COLOR color);
void ssd1307_DrawPixel(uint8_t x, uint8_t y, SSD1307_COLOR color);
char ssd1307_WriteChar(char ch, FontDef Font, SSD1307_COLOR color);
char ssd1307_WriteString(char* str, FontDef Font, SSD1307_COLOR color);
void ssd1307_SetCursor(uint8_t x, uint8_t y);
void ssd1307_InvertColors(void);
uint8_t ssd1307_WriteCommand(I2C_HandleTypeDef *hi2c, uint8_t command);
void SSD1307_animation_fill_square(I2C_HandleTypeDef *_hdisplay,
		uint32_t duration, uint8_t color, uint16_t width, uint16_t heigth);
void SSD1307_animation_scroll_window(I2C_HandleTypeDef *_hdisplay, char text[],
		uint32_t duration, uint8_t color, uint16_t height, FontDef fontType);
void SSD1307_animation_scroll_text(I2C_HandleTypeDef *_hdisplay, char *text,
		uint32_t duration, uint8_t color, uint16_t height, FontDef fontType);

void SSD1307_println(I2C_HandleTypeDef *_hdisplay, char *string, uint8_t color,
		FontDef fontType);



#endif  // _SSD1307_H
