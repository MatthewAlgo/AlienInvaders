#pragma once
#ifndef SPACE_SHIP_BULLET_H
#  define SPACE_SHIP_BULLET_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>

#include "VirtualBullet.h"

namespace GameNamespace {
  class SpaceShipBullet : public virtual VirtualBullet {
  public:
    SpaceShipBullet(sf::Vector2f WindowSize, sf::Texture Texture) : VirtualBullet(WindowSize, Texture) {}
        
    SpaceShipBullet() = default;
    ~SpaceShipBullet() = default;
  };
}  // namespace GameNamespace
#endif