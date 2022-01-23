#define tft_display_SCREEN_WIDTH 240
#define tft_display_SCREEN_HEIGHT 320

#define tft_display_COLOR_RGB(red, green, blue) (red << 16 | green << 8 | blue)
#define tft_display_COLOR_RANDOM() random(65535)
#define tft_display_COLOR_BLACK COLOR_RGB(0, 0, 0)

void tft_display_setup();

void tft_display_drawVerticalLine(unsigned int x, unsigned int y, unsigned int height, unsigned int color);

void tft_display_drawHorizontalLine(unsigned int x, unsigned int y, unsigned int width, unsigned int color);

void tft_display_drawRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color);

void tft_display_drawCircle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color);
