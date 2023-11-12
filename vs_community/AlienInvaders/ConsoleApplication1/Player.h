#pragma once

#include <string>

#include "alieninvadersretro/Controls.h"
#include "alieninvadersretro/SpaceShip.h"

class Player {
  // A player has a spaceship and a control method
  GameNamespace::SpaceShip* spaceShip;
  Controls* controls;
  std::string name;
  double score;

public:
  Player(GameNamespace::SpaceShip* spaceShip, Controls* controls);
  ~Player();
  // Factory for creating players
  Player* createPlayer(GameNamespace::SpaceShip* spaceShip, Controls* controls);
  Player* addControls(Controls* controls);
  Player* addSpaceShip(GameNamespace::SpaceShip* spaceShip);

  // Getters and setters for name and score
  std::string getName() const;

  void setName(std::string name);

  double getScore() const;

  void setScore(double score);

};
