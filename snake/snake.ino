#include "nes_controller.h"

void setup() {
  Serial.begin(9600);
  nes_controller_setup();
}


void loop() {
  nes_controller_reloadState();

  Serial.println("Top");
  if (nes_controller_buttonIsHeld(nes_controller_A_BUTTON)) {
    Serial.println("A_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_B_BUTTON)) {
    Serial.println("B_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_START_BUTTON)) {
    Serial.println("START_BUTTON ACTIVATED");
  }

  if (nes_controller_buttonIsHeld(nes_controller_SELECT_BUTTON)) {
    Serial.println("SELECT_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_UP_BUTTON)) {
    Serial.println("UP_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_DOWN_BUTTON)) {
    Serial.println("DOWN_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_LEFT_BUTTON)) {
    Serial.println("LEFT_BUTTON");
  }

  if (nes_controller_buttonIsHeld(nes_controller_RIGHT_BUTTON)) {
    Serial.println("RIGHT_BUTTON");
  }

  delay(100);
}
