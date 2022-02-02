void setup() {
    Serial.begin(9600);
}

int loopIndex = 0;

void loop() {
    Serial.println("loopIndex: " + String(loopIndex));
    delay(1000);
    loopIndex += 1;
}
