#include "Player.h"

Player::Player(GameNamespace::SpaceShip* spaceShip, Controls* controls): spaceShip(spaceShip), controls(controls) {}

Player::~Player() {
  delete spaceShip;
  delete controls;
}

Player* Player::createPlayer(GameNamespace::SpaceShip* spaceShip, Controls* controls) {
  return new Player(spaceShip, controls);
}

Player* Player::addControls(Controls* controls) {
  this->controls = controls;
  return this;
}

Player* Player::addSpaceShip(GameNamespace::SpaceShip* spaceShip) { this->spaceShip = spaceShip; }

std::string Player::getName() const { return name; }

void Player::setName(std::string name) { this->name = name; }

double Player::getScore() const {
  return score; }

void Player::setScore(double score) {
  this->score = score; }
