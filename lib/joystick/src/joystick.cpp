#include <Arduino.h>
float joystick_read(int pin) {
    float ratio = (analogRead(pin) / 512.0) - 1;
    return abs(ratio) < 0.40 ? 0 : ratio;
}
