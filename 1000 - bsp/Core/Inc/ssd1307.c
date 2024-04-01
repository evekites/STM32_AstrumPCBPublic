#include <ssd1307.h>
#include <main.h>

// Screenbuffer
static uint8_t SSD1307_Buffer[SSD1307_WIDTH * SSD1307_HEIGHT / 8];

// Screen object
static SSD1307_t SSD1307;


extern uint32_t millis;
extern I2C_HandleTypeDef hi2c1;
extern LPTIM_HandleTypeDef hlptim1;
//
//  Send a byte to the command register
//
uint8_t ssd1307_WriteCommand(I2C_HandleTypeDef *hi2c, uint8_t command)
{
	return HAL_I2C_Mem_Write(hi2c, SSD1307_I2C_ADDR, 0x00, 1, &command, 1, 10);
}

uint8_t ssd1307_Init(I2C_HandleTypeDef *hi2c, uint8_t orientation){
	//reset screen
	HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, 0);
	HAL_Delay(10);
	HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, 1);

	// Wait for the screen to boot
	HAL_Delay(100);
	int status = 0;

	//    // Init LCD
	status += ssd1307_WriteCommand(hi2c, 0xAE);   // Display off

	status += ssd1307_WriteCommand(hi2c, 0x20);   // Set Memory Addressing Mode
	status += ssd1307_WriteCommand(hi2c, 0x10);   // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid

	status += ssd1307_WriteCommand(hi2c, 0xB0);   // Set Page Start Address for Page Addressing Mode,0-4



	status += ssd1307_WriteCommand(hi2c, 0x00);   // Set low column address

	status += ssd1307_WriteCommand(hi2c, 0x10);   // Set high column address

	status += ssd1307_WriteCommand(hi2c, 0x40);   // Set start line address 40-66

	status += ssd1307_WriteCommand(hi2c, 0x81);   // set contrast control register
	status += ssd1307_WriteCommand(hi2c, 0xFF);

	status += ssd1307_WriteCommand(hi2c, 0xA6);   // Set normal display

	if(orientation == 0){
		status += ssd1307_WriteCommand(hi2c, 0xA1);   // Set segment re-map 0 to 127

		status += ssd1307_WriteCommand(hi2c, 0xC0);   // Set COM Output Scan Direction
	}else if(orientation == 3){
		status += ssd1307_WriteCommand(hi2c, 0xA0);   // Set segment re-map 0 to 127

		status += ssd1307_WriteCommand(hi2c, 0xC8);   // Set COM Output Scan Direction
	}


	status += ssd1307_WriteCommand(hi2c, 0xA8);   // Set multiplex ratio(1 to 64)
	status += ssd1307_WriteCommand(hi2c, SSD1307_HEIGHT - 1);

	status += ssd1307_WriteCommand(hi2c, 0xA4);   // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content

	status += ssd1307_WriteCommand(hi2c, 0xD3);   // Set display offset
	status += ssd1307_WriteCommand(hi2c, 0x00);   // No offset

	status += ssd1307_WriteCommand(hi2c, 0xD5);   // Set display clock divide ratio/oscillator frequency
	status += ssd1307_WriteCommand(hi2c, 0xF0);   // Set 0x[1][2] : [clock speed] and [divide ratio]

	status += ssd1307_WriteCommand(hi2c, 0xD9);   // Set pre-charge period
	status += ssd1307_WriteCommand(hi2c, 0x22);

	status += ssd1307_WriteCommand(hi2c, 0xDA);   // Set com pins hardware configuration
	status += ssd1307_WriteCommand(hi2c, SSD1307_COM_LR_REMAP << 5 | SSD1307_COM_ALTERNATIVE_PIN_CONFIG << 4 | 0x02);

	status += ssd1307_WriteCommand(hi2c, 0xDB);   // Set vcomh
	status += ssd1307_WriteCommand(hi2c, 0x20);   // 0x20,0.77xVcc

	status += ssd1307_WriteCommand(hi2c, 0xAF);   // Turn on ssd1307 panel

	if (status != 0) {
		return 1;
	}

	// Clear screen
	ssd1307_Fill(Black);

	// Flush buffer to screen
	ssd1307_UpdateScreen(hi2c);

	// Set default values for screen object
	SSD1307.CurrentX = 0;
	SSD1307.CurrentY = 0;

	SSD1307.Initialized = 1;

	return 0;
}

//
//  Fill the whole screen with the given color
//
void ssd1307_Fill(SSD1307_COLOR color)
{
	// Fill screenbuffer with a constant value (color)
	uint32_t i;

	for(i = 0; i < sizeof(SSD1307_Buffer); i++)
	{
		SSD1307_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

//
//  Write the screenbuffer with changed to the screen
//
void ssd1307_UpdateScreen(I2C_HandleTypeDef *hi2c)
{
	uint8_t i;

	for (i = 0; i < 5; i++) {
		ssd1307_WriteCommand(hi2c, 0xB0 + i);
		ssd1307_WriteCommand(hi2c, 0x00);
		ssd1307_WriteCommand(hi2c, 0x10);

		HAL_I2C_Mem_Write(hi2c, SSD1307_I2C_ADDR, 0x40, 1, &SSD1307_Buffer[SSD1307_WIDTH * i], SSD1307_WIDTH, 100);
	}
}

//
//  Draw one pixel in the screenbuffer
//  X => X Coordinate
//  Y => Y Coordinate
//  color => Pixel color
//
void ssd1307_DrawPixel(uint8_t x, uint8_t y, SSD1307_COLOR color)
{
	if (x >= SSD1307_WIDTH || y >= SSD1307_HEIGHT)
	{
		// Don't write outside the buffer
		return;
	}

	// Check if pixel should be inverted
	if (SSD1307.Inverted)
	{
		color = (SSD1307_COLOR)!color;
	}

	// Draw in the correct color
	if (color == White)
	{
		SSD1307_Buffer[x + (y / 8) * SSD1307_WIDTH] |= 1 << (y % 8);
	}
	else
	{
		SSD1307_Buffer[x + (y / 8) * SSD1307_WIDTH] &= ~(1 << (y % 8));
	}
}

//
//  Draw 1 char to the screen buffer
//  ch      => Character to write
//  Font    => Font to use
//  color   => Black or White
//
char ssd1307_WriteChar(char ch, FontDef Font, SSD1307_COLOR color)
{
	uint32_t i, b, j;
	if(ch < 32) return ch;
	// Check remaining space on current line
	if (SSD1307_WIDTH <= (SSD1307.CurrentX + Font.FontWidth) ||
			SSD1307_HEIGHT <= (SSD1307.CurrentY + Font.FontHeight))
	{
		// Not enough space on current line
		return 0;
	}

	// Translate font to screenbuffer
	for (i = 0; i < Font.FontHeight; i++)
	{
		b = Font.data[(ch - 32) * Font.FontHeight + i];
		for (j = 0; j < Font.FontWidth; j++)
		{
			if ((b << j) & 0x8000)
			{
				ssd1307_DrawPixel(SSD1307.CurrentX + j, (SSD1307.CurrentY + i), (SSD1307_COLOR) color);
			}
			else
			{
				ssd1307_DrawPixel(SSD1307.CurrentX + j, (SSD1307.CurrentY + i), (SSD1307_COLOR)!color);
			}
		}
	}

	// The current space is now taken
	SSD1307.CurrentX += Font.FontWidth;

	// Return written char for validation
	return ch;
}

//
//  Write full string to screenbuffer
//
char ssd1307_WriteString(char* str, FontDef Font, SSD1307_COLOR color)
{
	// Write until null-byte
	while (*str)
	{
		if (*str == '\t') {
			for(int i = 0; i < TAB_SIZE; i++){
				ssd1307_WriteChar(' ', Font, color);
			}
		}

		if (ssd1307_WriteChar(*str, Font, color) != *str)
		{
			// Char could not be written
			return *str;
		}

		// Next char
		str++;
	}

	// Everything ok
	return *str;
}

//
//  Invert background/foreground colors
//
void ssd1307_InvertColors(void)
{
	SSD1307.Inverted = !SSD1307.Inverted;
}

//
//  Set cursor position
//
void ssd1307_SetCursor(uint8_t x, uint8_t y)
{
	SSD1307.CurrentX = x;
	SSD1307.CurrentY = y;
}


void SSD1307_animation_fill_square(I2C_HandleTypeDef *_hdisplay, uint32_t duration, uint8_t color, uint16_t width, uint16_t heigth){
	uint32_t t_start_pixelFillAnimation = 0;
	uint32_t pixel_count = 0;

	//fill animation connected to time.
	for(int y = 0; y < heigth; y++){
		//save start time
		if(!t_start_pixelFillAnimation) t_start_pixelFillAnimation = millis;

		for(int x = 0; x < width; x++){
			ssd1307_DrawPixel(x, y, color);

			/*slow animation down then pixels are filling too fast by updating screen which takes a significant amount of time*/
			if(pixel_count >  (((double)(width*heigth)/(double)duration) * (millis - t_start_pixelFillAnimation)) || (x == (width-1) && y == (heigth-1))){
				ssd1307_UpdateScreen(_hdisplay);
			}
			pixel_count++;
		}
	}
	t_start_pixelFillAnimation = 0;
	pixel_count = 0;
}

void SSD1307_animation_scroll_window(I2C_HandleTypeDef *_hdisplay,  char text[], uint32_t duration, uint8_t color, uint16_t height, FontDef fontType){
	uint32_t t_start_textScrollAnimation = 0;


	//scroll text
	for(int i = 0; i < SSD1307_WIDTH; i++){
		if(!t_start_textScrollAnimation) t_start_textScrollAnimation = millis;
		ssd1307_Fill(!color);
		ssd1307_SetCursor(i, height);
		ssd1307_WriteString(text, fontType, color);

		/*slow animation down then pixels are filling too fast by updating screen which takes a significant amount of time*/
		if(i >  (((double)SSD1307_WIDTH/(double)duration) * (millis - t_start_textScrollAnimation)) || (i == (SSD1307_WIDTH-1))){
			ssd1307_UpdateScreen(_hdisplay);
		}
	}
	t_start_textScrollAnimation = 0;


	ssd1307_Fill(!color);
	ssd1307_UpdateScreen(&hi2c1);
}

void SSD1307_animation_scroll_text(I2C_HandleTypeDef *_hdisplay, char *text, uint32_t duration, uint8_t color, uint16_t height, FontDef fontType){
	uint32_t t_start_textScrollAnimation = millis;
	char buffer[500];
	strcpy(buffer, "");

	//calculate and create padding in front of string
	for(int i = 0; i < (SSD1307_WIDTH/fontType.FontWidth); i++){
		strcat(buffer, " ");
	}

	//add text in buffer
	strcat(buffer, text);

	int len = strlen(buffer);

	for (int i = 0; i < len; i++) {
		ssd1307_Fill(!color);
		ssd1307_SetCursor(0, height);
		ssd1307_WriteString(&buffer[i], fontType, color);
		ssd1307_UpdateScreen(_hdisplay);
		//delay
		while(i > (((double)len/((double)duration)) * (millis - t_start_textScrollAnimation)));

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
void SSD1307_println(I2C_HandleTypeDef *_hdisplay, char *string, uint8_t color,  FontDef fontType){
	const int line_amount = (int)floor((float)SSD1307_HEIGHT/(float)fontType.FontHeight);

	static char screen_text_buffer[10][SSD1307_WIDTH] = {""};
	static uint8_t line = 0; //line number that the current 'console' is at

	if(line >= line_amount){
		line--;

		//move all lines up one line, discarding ones going out of bound
		for(int i = 0; i < line_amount-1; i++){
			strcpy(screen_text_buffer[i], screen_text_buffer[i+1]);
		}
	}

	//write string
	if(strlen(string) < 128){
		strcpy(screen_text_buffer[line], string);
	}else{
		strcpy(screen_text_buffer[line], "Size ERROR");
	}

	ssd1307_Fill(!color);
	for(int i = 0; i < line_amount; i++){
		ssd1307_SetCursor(0, (fontType.FontHeight)*i);
		ssd1307_WriteString(screen_text_buffer[i], fontType, color);
	}

	line++;
	ssd1307_UpdateScreen(&DISPLAY0);
}





