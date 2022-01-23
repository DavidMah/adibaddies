#define JOY_X A0
#define JOY_Y A1

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Values range from 0 to 1023 inclusive
    int xValue = analogRead(JOY_X);
    int yValue = analogRead(JOY_Y);

    Serial.print(xValue);
    Serial.print("\t");
    Serial.print(yValue);
    Serial.println("");
    delay(100);
}
