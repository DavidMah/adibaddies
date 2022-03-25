#include <Arduino.h>

void linear_potentiometer_setup(int pin) {
    pinMode(pin, INPUT);
}

float linear_potentiometer_read(int pin) {
    return analogRead(pin) / 1024.0;
}
