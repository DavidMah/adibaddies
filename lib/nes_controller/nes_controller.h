#define nes_controller_A_BUTTON         0
#define nes_controller_B_BUTTON         1
#define nes_controller_SELECT_BUTTON    2
#define nes_controller_START_BUTTON     3
#define nes_controller_UP_BUTTON        4
#define nes_controller_DOWN_BUTTON      5
#define nes_controller_LEFT_BUTTON      6
#define nes_controller_RIGHT_BUTTON     7


void nes_controller_setup();

boolean nes_controller_buttonIsHeld(int button);
