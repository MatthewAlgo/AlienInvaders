#pragma once
#ifndef ENEMY_SPACESHIP_BULLET_H
#  define ENEMY_SPACESHIP_BULLET_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>

#include "VirtualBullet.h"

#  pragma region ENEMY_SPACESHIP_BULLET
namespace GameNamespace {
  class EnemySpaceShipBullet : public virtual VirtualBullet {
  protected:
    unsigned int DAMAGE = BULLET_DAMAGE_AMOUNT_DEFAULT;

  public:
    inline static int DAMAGE_SUPPLIER = 0; // The enemies have increased damage as the game progresses 
    EnemySpaceShipBullet(sf::Vector2f WindowSize, sf::Texture Texture) : VirtualBullet(WindowSize, Texture) { type = BULLET;}
    EnemySpaceShipBullet() = default;
    virtual ~EnemySpaceShipBullet() = default;

  };
}  // namespace GameNamespace
#  pragma endregion ENEMY_SPACESHIP_BULLET
#endif  // ! ENEMY_SPACESHIP_BULLET_H