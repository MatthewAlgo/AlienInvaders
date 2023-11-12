#pragma once
#ifndef VIRTUAL_SPACE_SHIP_HEADER_H
#  define VIRTUAL_SPACE_SHIP_HEADER_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <deque>
#  include <vector>
#  include <memory>

#  include "SpaceShipBullet.h"

#  pragma region V_SPACESHIP_CLASS
namespace GameNamespace {
  class VirtualSpaceShip : public virtual VirtualEntity {
  private:
    // Each entitiy has its own stack of bullets
    std::deque<std::unique_ptr<SpaceShipBullet>> BulletDeque; // The bullet vector that each spaceship has
  public:
    // Constructors
    VirtualSpaceShip(sf::Vector2f WindowSize, sf::Texture Texture);
    VirtualSpaceShip(sf::Vector2f WindowSize);
    VirtualSpaceShip();
    
    virtual ~VirtualSpaceShip() = default;        // Default destructor

    // Interact with the enemy
    inline void MoveUp(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) override;
    inline void MoveDown(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) override;
    inline void MoveLeft(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) override;
    inline void MoveRight(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) override;
    
  };
}  // namespace GameNamespace
#  pragma endregion V_SPACESHIP_CLASS

#endif