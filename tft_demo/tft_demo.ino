#include <tft_display.h>

void setup()
{
    tft_display_setup();
    tft_display_drawRectangle(0, 0, tft_display_SCREEN_WIDTH, tft_display_SCREEN_HEIGHT, tft_display_COLOR_RGB(0, 0, 0));
}

void loop() {

    tft_display_drawRectangle(200, 20, 50, 100, tft_display_COLOR_RANDOM());
    tft_display_drawCircle(150, 100, 50, tft_display_COLOR_RANDOM());
    tft_display_drawRectangle(50, 50, 15, 30, tft_display_COLOR_RANDOM());

    delay(1000);
}
