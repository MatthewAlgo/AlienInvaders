#include "alieninvadersretro/VirtualSpaceShip.h"

namespace GameNamespace {
  VirtualSpaceShip::VirtualSpaceShip(sf::Vector2f WindowSize, sf::Texture Texture)
      : VirtualEntity(WindowSize, Texture) {
    // Init the explosion if this constructor is called
    POS.y = WindowSize.y / 2;
    POS.x = WindowSize.x / 2;
    // Set the position of the spaceship
    SpriteOfEntity.setTexture(TextureOfEntity);
    SpriteOfEntity.setPosition(sf::Vector2f(POS.x, POS.y));

    // Init the explosion
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  }

  VirtualSpaceShip::VirtualSpaceShip(sf::Vector2f WindowSize)
      : VirtualEntity(WindowSize) {
    // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  }
  VirtualSpaceShip::VirtualSpaceShip() {
    // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  }

  inline void VirtualSpaceShip::MoveUp(int amount) {
    if (POS.y - 20 > 0 && POS.y - 20 < WinSize.y) POS.y -= 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  inline void VirtualSpaceShip::MoveDown(int amount) {
    if (POS.y + 20 > 0 && POS.y + 20 < WinSize.y) POS.y += 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  inline void VirtualSpaceShip::MoveLeft(int amount) {
    if (POS.x - 20 > -60 && POS.x - 20 < WinSize.x) POS.x -= 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  inline void VirtualSpaceShip::MoveRight(int amount) {
    if (POS.x + 20 > -60 && POS.x + 20 < WinSize.x) POS.x += 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

}  // namespace GameNamespace