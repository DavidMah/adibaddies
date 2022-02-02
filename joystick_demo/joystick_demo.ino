#include <joystick.h>

// Yellow Cable
#define JOY_X A8
// Blue Cable
#define JOY_Y A9

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Values range from 0 to 1023 inclusive
    /* float xValue = analogRead(JOY_X)*/
    /* float yValue = analogRead(JOY_Y)*/

    // Values range from -1.0 to 1.0 inclusive
    float xValue = joystick_read(JOY_X);
    float yValue = joystick_read(JOY_Y);

    Serial.print(xValue);
    Serial.print("\t");
    Serial.print(yValue);
    Serial.println("");
    delay(100);
}
