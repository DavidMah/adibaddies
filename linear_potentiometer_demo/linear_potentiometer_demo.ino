#include <linear_potentiometer.h>
#define LP_PIN A5

void setup() {
    Serial.begin(9600);

    linear_potentiometer_setup(LP_PIN);
}

void loop() {
    float raw = linear_potentiometer_read(LP_PIN);
    Serial.println(raw);
    delay(25);
}
