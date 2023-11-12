#pragma once
#ifndef V_BULLET_H
#  define V_BULLET_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>

#include "VirtualEntity.h"

enum bulletMovementAmout {
  BULLET_MOVEMENT_AMOUNT_DEFAULT = 30,
  BULLET_MOVEMENT_AMOUNT_FAST = 60,
  BULLET_MOVEMENT_AMOUNT_SLOW = 15
};
enum bulletDamageAmount {
  BULLET_DAMAGE_AMOUNT_DEFAULT = 1,
  BULLET_DAMAGE_AMOUNT_MORE = 2,
  BULLET_DAMAGE_AMOUNT_EVENMORE = 3 
};

namespace GameNamespace {
  class VirtualBullet : public virtual VirtualEntity {
  protected:
    unsigned int DAMAGE = BULLET_DAMAGE_AMOUNT_DEFAULT;
    
    // It produces explosions on its bullet collisions -> their data is located here
    sf::Texture Explosion;
    sf::Sprite ExplosionSprite;

  public:
    VirtualBullet(sf::Vector2f WindowSize, sf::Texture Texture) : VirtualEntity(WindowSize, Texture) { type = BULLET; }
    VirtualBullet() = default;
    virtual ~VirtualBullet() = default;

    virtual void MoveUp(int amount = BULLET_MOVEMENT_AMOUNT_DEFAULT) override {
      POS.y -= amount;
      SpriteOfEntity.setPosition(POS.x, POS.y);
    }

    virtual void MoveDown(int amount = BULLET_MOVEMENT_AMOUNT_DEFAULT) override {
      POS.y += amount;
      SpriteOfEntity.setPosition(POS.x, POS.y);
    }

    virtual unsigned int getDamage() { return DAMAGE; }
    virtual void setDamage(unsigned int D) { DAMAGE = D; }
  };
}  // namespace GameNamespace
#endif