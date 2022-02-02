#define tft_display_SCREEN_WIDTH 240
#define tft_display_SCREEN_HEIGHT 320

// not supported until i figure out the actual equation
// #define tft_display_COLOR_RGB(red, green, blue) (((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255);

#define	tft_display_COLOR_BLACK   0x0000
#define	tft_display_COLOR_BLUE    0x001F
#define	tft_display_COLOR_RED     0xF800
#define	tft_display_COLOR_GREEN   0x07E0
#define tft_display_COLOR_CYAN    0x07FF
#define tft_display_COLOR_MAGENTA 0xF81F
#define tft_display_COLOR_YELLOW  0xFFE0
#define tft_display_COLOR_WHITE   0xFFFF

#define tft_display_COLOR_RANDOM() random(65535)

void tft_display_setup();

void tft_display_drawVerticalLine(unsigned int x, unsigned int y, unsigned int height, unsigned int color);

void tft_display_drawHorizontalLine(unsigned int x, unsigned int y, unsigned int width, unsigned int color);

void tft_display_drawRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color);

void tft_display_moveRectangle(unsigned int priorX, unsigned int priorY, unsigned int width, unsigned int height, unsigned int color, unsigned int backgroundColor, unsigned int newX, unsigned int newY);

void tft_display_drawCircle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color);
