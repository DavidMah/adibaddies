#include "tft_display.h"

void setup()
{
    tft_display_setup();
}

void loop() {
    for (int x = 0; x < tft_display_SCREEN_WIDTH; x+=1) {
        tft_display_drawVerticalLine(0, x, tft_display_SCREEN_WIDTH, tft_display_COLOR_RGB(0, 0, 0));
    }
    delay(1000);

    int startX = 20;
    int startY = 20;

    unsigned int color = tft_display_COLOR_RANDOM();
    for (int i = 0; i < 50; i+=1) {
        tft_display_drawVerticalLine(startX, startY+i, 100, color);
    }

    /* for (int i = 0; i < 50; i+=1) {*/

    /* }*/

    delay(2000);
}
