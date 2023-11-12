#include "alieninvadersretro/Controls.h"
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "alieninvadersretro/SpaceShip.h"

// Define the controls required for the game
Controls::Controls(short ctrl_type, GameNamespace::SpaceShip* spaceShip) : control_type(ctrl_type) {
  // Create the controls elements in here
  // Each player accepts a control method on initialization
  // The control method is defined by the control_type
  switch (ctrl_type) {
    case KEYBOARD_ARROWS_CONTROL_TYPE:
      // Create the controls for the keyboard arrows
      // Create the controls class and handle the controls for each player here
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        spaceShip->MoveLeft();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        spaceShip->MoveRight();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        spaceShip->MoveUp();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        spaceShip->MoveDown();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        spaceShip->Shoot();
      }
      break;
    case WASD_KEYBOARD_CONTROL_TYPE:
      // Create the controls for the WASD keyboard
      break;
    case BLUETOOTH_KEYS_CONNECTIVITY_CONTROL_TYPE:
      // Create the controls for the bluetooth keys
      break;
    case BLUETOOTH_ACCELEROMETER_CONTROL_TYPE:
      // Create the controls for the bluetooth accelerometer
      break;
    case BLUETOOTH_JOYSTICK_CONTROL_TYPE:
      // Create the controls for the bluetooth joystick
      break;
    case SERIAL_PORT_CONTROL_TYPE:
      // Create the controls for the serial port
      break; // Create the controls for the serial port
  }
}
