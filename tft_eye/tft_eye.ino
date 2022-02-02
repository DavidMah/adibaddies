#include <joystick.h>
#include <tft_display.h>

#define EYE_COLOR tft_display_COLOR_RED
#define EYE_LENGTH 50
#define BACKGROUND_COLOR tft_display_COLOR_BLACK

#define JOY_X A8 // Yellow Cable
#define JOY_Y A9 // Blue Cable


int xPos = 100;
int yPos = 100;

void setup()
{
    tft_display_setup();
    tft_display_drawRectangle(0, 0, tft_display_SCREEN_WIDTH,
                              tft_display_SCREEN_HEIGHT, BACKGROUND_COLOR);
    tft_display_drawRectangle(xPos, yPos, EYE_LENGTH, EYE_LENGTH, EYE_COLOR);
}

void loop() {

    int priorXPos = xPos;
    int priorYPos = yPos;
    float xRatio = joystick_read(JOY_X);
    float yRatio = joystick_read(JOY_Y);
    xPos = max(min(xPos + int(xRatio * 10), tft_display_SCREEN_WIDTH), 0);
    yPos = max(min(yPos + int((yRatio * -1) * 10), tft_display_SCREEN_HEIGHT), 0);

    tft_display_moveRectangle(
        priorXPos, priorYPos, EYE_LENGTH, EYE_LENGTH, EYE_COLOR,
        BACKGROUND_COLOR,
        xPos, yPos
    );

    delay(10);
}
