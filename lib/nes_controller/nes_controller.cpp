#include "Arduino.h"
#include "nes_controller.h"

#define NES_DATA_PIN 4
#define NES_CLOCK_PIN 2
#define NES_LATCH_PIN 3

#define A_BUTTON         nes_controller_A_BUTTON         
#define B_BUTTON         nes_controller_B_BUTTON         
#define SELECT_BUTTON    nes_controller_SELECT_BUTTON    
#define START_BUTTON     nes_controller_START_BUTTON     
#define UP_BUTTON        nes_controller_UP_BUTTON        
#define DOWN_BUTTON      nes_controller_DOWN_BUTTON      
#define LEFT_BUTTON      nes_controller_LEFT_BUTTON      
#define RIGHT_BUTTON     nes_controller_RIGHT_BUTTON     


byte nesRegister = 0;

void nes_controller_setup() {
  // Set appropriate pins to inputs
  pinMode(NES_DATA_PIN, INPUT);

  // Set appropriate pins to outputs
  pinMode(NES_CLOCK_PIN, OUTPUT);
  pinMode(NES_LATCH_PIN, OUTPUT);

  // Set initial states
  digitalWrite(NES_CLOCK_PIN, LOW);
  digitalWrite(NES_LATCH_PIN, LOW);
}


byte readNesController() {
  // Pre-load a variable with all 1's which assumes all buttons are not
  // pressed. But while we cycle through the bits, if we detect a LOW, which is
  // a 0, we clear that bit. In the end, we find all the buttons states at once.
  int tempData = 255;

  // Quickly pulse the NES_LATCH_PIN pin so that the register grab what it see on
  // its parallel data pins.
  digitalWrite(NES_LATCH_PIN, HIGH);
  digitalWrite(NES_LATCH_PIN, LOW);

  // Upon latching, the first bit is available to look at, which is the state
  // of the A button. We see if it is low, and if it is, we clear out variable's
  // first bit to indicate this is so.
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, A_BUTTON);

  // Clock the next bit which is the B button and determine its state just like
  // we did above.
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, B_BUTTON);

  // Now do this for the rest of them!

  // Select button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, SELECT_BUTTON);

  // Start button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, START_BUTTON);

  // Up button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, UP_BUTTON);

  // Down button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, DOWN_BUTTON);

  // Left button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, LEFT_BUTTON);

  // Right button
  digitalWrite(NES_CLOCK_PIN, HIGH);
  digitalWrite(NES_CLOCK_PIN, LOW);
  if (digitalRead(NES_DATA_PIN) == LOW)
    bitClear(tempData, RIGHT_BUTTON);

  // After all of this, we now have our variable all bundled up
  // with all of the NES button states.*/
  return tempData;
}

void nes_controller_reloadState() {
  nesRegister = readNesController();
}

boolean nes_controller_buttonIsHeld(int button) {
  return bitRead(nesRegister, button) == 0;
}
