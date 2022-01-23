#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    144
#define FLIP_INTERVAL 2
#define SNAKE_LENGTH 10
#define ITERATION_DURATION 25 // milliseconds
#define ITERATIONS_WITHIN_ERA 255

#define ENABLE_ROTARY false
#define ROTARY_CLOCK_PIN 9
#define ROTARY_DT_PIN 8

CRGB leds[NUM_LEDS];

int iteration = 0;
float secondsSoFar = 0;

int primaryColor[3] = {0, 0, 0};
int secondaryColor[3] = {0, 0, 0};

int rotaryPosition = 10;
int rotaryRotation;
int rotaryValue;
boolean rotaryLeftRight;

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);
    iteration = 0;

    if (ENABLE_ROTARY) {
        pinMode(ROTARY_CLOCK_PIN, INPUT);
        pinMode(ROTARY_DT_PIN, INPUT);
        rotaryRotation = digitalRead(ROTARY_CLOCK_PIN);
    }
}

void loop() {
    float brightness;
    if (ENABLE_ROTARY) {
        rotaryValue = digitalRead(ROTARY_CLOCK_PIN);
        if (rotaryValue != rotaryRotation) {
            if (digitalRead(ROTARY_DT_PIN) != rotaryValue) {
                rotaryPosition += 1;
                rotaryLeftRight = true;
            } else {
                rotaryPosition -= 1;
                rotaryLeftRight = false;
            }
        }
        brightness = min(max((rotaryPosition + 10.0) / 20.0, 0), 20);
        rotaryRotation = rotaryValue;
    } else {
        brightness = 1.0;
    }

    int litUpIndex = iteration % NUM_LEDS;

    for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex +=1 ) {
        int red = 0;
        int green = 0;
        int blue = 0;

        int motion = iteration;

        boolean flipColors =  (int(secondsSoFar) % (FLIP_INTERVAL*2) < FLIP_INTERVAL);
        boolean isEvenChunk = ((ledIndex + (motion)) / SNAKE_LENGTH) % 2 == 0;

        boolean isPrimaryColor = isEvenChunk;
        if (flipColors) {
            // no flip for now
            // isPrimaryColor = !isPrimaryColor;
        }

        int iterationWithinEra = (iteration + (ledIndex*5) + (3*iteration)) % (ITERATIONS_WITHIN_ERA * 3);
        int chapter = iterationWithinEra / ITERATIONS_WITHIN_ERA;
        int iterationWithinChapter = iterationWithinEra % ITERATIONS_WITHIN_ERA;
        primaryColor[0] = (
                              chapter == 0 ? iterationWithinChapter :
                              chapter == 1 ? ITERATIONS_WITHIN_ERA - iterationWithinChapter :
                              0
                          );
        primaryColor[1] = (
                              chapter == 0 ? 0 :
                              chapter == 1 ? iterationWithinChapter :
                              ITERATIONS_WITHIN_ERA - iterationWithinChapter
                          );
        primaryColor[2] = (
                              chapter == 0 ? ITERATIONS_WITHIN_ERA - iterationWithinChapter :
                              chapter == 1 ? 0 :
                              iterationWithinChapter
                          );

        if (isPrimaryColor) {
            red = primaryColor[0];
            green = primaryColor[1];
            blue = primaryColor[2];
        } else {
            red = secondaryColor[0];
            green = secondaryColor[1];
            blue = secondaryColor[2];
        }

        red = int(red * brightness);
        blue = int(blue * brightness);
        green = int(green * brightness);

        leds[ledIndex] = CRGB(red, green, blue);
    }
    FastLED.show();
    delay(ITERATION_DURATION);
    iteration += 1;

    secondsSoFar += (ITERATION_DURATION / 1000.0);
}
