#pragma once

enum CONTROLS_TYPES {
  KEYBOARD_ARROWS_CONTROL_TYPE,
  WASD_KEYBOARD_CONTROL_TYPE,
  BLUETOOTH_KEYS_CONNECTIVITY_CONTROL_TYPE,
  BLUETOOTH_ACCELEROMETER_CONTROL_TYPE,
  BLUETOOTH_JOYSTICK_CONTROL_TYPE,
  SERIAL_PORT_CONTROL_TYPE
};

/*
  This class defines the controls for the game. Each player should have a controls instance that is
  mapped to a specific key. For example, if another player enters the game and wants WASD controls,
  they can be chosen here
*/

class Controls {
private:
  short control_type;

public:
  Controls(short ctrl_type);
};


