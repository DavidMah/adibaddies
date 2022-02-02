// Yellow Cable: X
// Blue Cable: Y
// Both should go into A# pins
// Returns between -1.0 and 1.0, and does not include values
// between -0.4 and 0.4 to minimize noise.
float joystick_read(int pin);
