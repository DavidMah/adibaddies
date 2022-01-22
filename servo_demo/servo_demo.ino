#include <Servo.h>

#define SERVO_PIN 6

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}
void loop() {
  for (int i = 0; i < 180; i += 10) {
    Serial.println(i);
    servo.write(i);
    delay(1000);
  }
}
