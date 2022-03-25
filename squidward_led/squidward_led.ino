#include <FastLED.h>
#include <linear_potentiometer.h>
#include <chapter.h>

#define LED_PIN     7
#define NUM_LEDS    12
#define LP_PIN A5

#define CHAPTERS_PER_ERA 3
#define TICKS_PER_CHAPTER 155
#define MS_PER_TICK 10

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    linear_potentiometer_setup(LP_PIN);
    chapter_setup(CHAPTERS_PER_ERA, TICKS_PER_CHAPTER, MS_PER_TICK);
}

void loop() {
    ChapterInfo chapterInfo = chapter_read();

    Serial.print(chapterInfo.era);
    Serial.print(", ");
    Serial.print(chapterInfo.chapter);
    Serial.print(", ");
    Serial.print(chapterInfo.chapterInverse);
    Serial.print(", ");
    Serial.print(chapterInfo.tick);
    Serial.print(", ");
    Serial.print(chapterInfo.tickInverse);
    Serial.print(", ");
    Serial.print(chapterInfo.ms);
    Serial.println("");

    float lpRatio = linear_potentiometer_read(LP_PIN);

    for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex +=1) {
        int red = 100 + chapterInfo.tick;
        int green = 100 + chapterInfo.tick;
        int blue = 100 + chapterInfo.tick;

        red = int(red * lpRatio);
        green = int(green * lpRatio);
        blue = int(blue * lpRatio);

        leds[ledIndex] = CRGB(red, green, blue);
    }
    FastLED.show();
    delay(10);
}
