#include <Servo.h>

#define JOY_Y_PIN A0
#define JOY_X_PIN A1
#define INTERVAL 50
#define SERVO_X_PIN 5
#define SERVO_Y_PIN 3

#define JOY_TO_RATIO(joy) ((joy - 512) / 512.0)
/* #define RATIO_TO_DELTA(ratio) (ratio * (10 / (INTERVAL / 100.0)))*/
#define RATIO_TO_DELTA(ratio) (ratio * 10)

#define SERIAL_DEBUG_RATE 10
#define SERIAL_DEBUG true // Uncomment to add Serial printing debug statements

Servo servoX;
Servo servoY;

float servoXPos = 90.0;
float servoYPos = 90.0;
int loopIndex = 0;

void setup() {
    Serial.begin(9600);
    servoX.attach(SERVO_X_PIN);
    servoY.attach(SERVO_Y_PIN);
}

void loop() {
#ifdef SERIAL_DEBUG
    /* Serial.println("loopIndex: " + String(loopIndex));*/
#endif /* SERIAL_DEBUG */
    float xInput = RATIO_TO_DELTA(JOY_TO_RATIO(analogRead(JOY_X_PIN))) * -1;
    float yInput = RATIO_TO_DELTA(JOY_TO_RATIO(analogRead(JOY_Y_PIN)));

    if (abs(xInput) > 0.1) {
        servoXPos = min(max(servoXPos + xInput, 0), 180);
    }

    if (abs(yInput) > 0.1) {
        servoYPos = min(max(servoYPos + yInput, 0), 180);
    }

#ifdef SERIAL_DEBUG
    if (loopIndex % SERIAL_DEBUG_RATE == 0) {
        Serial.println("input: " + String(xInput) + ":" + String(yInput));
        Serial.println("position: " + String(servoXPos) + ":" + String(servoYPos));
    }
#endif /* SERIAL_DEBUG */

    servoX.write(int(servoXPos));
    servoY.write(int(servoYPos));

    delay(INTERVAL);
    loopIndex += 1;
}
