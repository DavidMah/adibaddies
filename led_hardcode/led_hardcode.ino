#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    144
#define  RED 100
#define  BLUE 150
#define  GREEN 50

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex +=1 ) {
    leds[ledIndex] = CRGB(RED,    GREEN, BLUE);
  }
  FastLED.show();
	delay(1000);
}
