#include "alieninvadersretro/VirtualEntity.h"

namespace MatthewsNamespace {
  VirtualEntity::VirtualEntity(sf::Vector2f WindowSize, sf::Texture Texture)
      : WinSize(WindowSize), TextureOfEntity(Texture) {
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

  inline void VirtualEntity::MoveUp() {
    if (POS.y - 20 > 0 && POS.y - 20 < WinSize.y) POS.y -= 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void VirtualEntity::MoveDown() {
    if (POS.y + 20 > 0 && POS.y + 20 < WinSize.y) POS.y += 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void VirtualEntity::MoveLeft() {
    if (POS.x - 20 > -60 && POS.x - 20 < WinSize.x) POS.x -= 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void VirtualEntity::MoveRight() {
    if (POS.x + 20 > -60 && POS.x + 20 < WinSize.x) POS.x += 30;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  VirtualEntity::VirtualEntity(sf::Vector2f WindowSize) : WinSize(WindowSize) {
    // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  }
  VirtualEntity::VirtualEntity() {
    // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  }

  /// Implement a definition for the virtual functions

  // Functions initially placed inside the header file
  void VirtualEntity::setTexture(sf::Texture& texture) { TextureOfEntity = texture; }
  void VirtualEntity::setSprite(sf::Sprite& sprite) { SpriteOfEntity = sprite; }
  void VirtualEntity::setSpaceShipPosition(double X, double Y) {
    POS.x = X;
    POS.y = Y;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  void VirtualEntity::setLife(short L) { EntityLife = L; }
  void VirtualEntity::setMainWindowSize(int X, int Y) {
    WinSize.x = X;
    WinSize.y = Y;
  }

  sf::Texture* VirtualEntity::getSpaceShipTexture() { return &TextureOfEntity; }
  sf::Sprite* VirtualEntity::getSpaceShipSprite() { return &SpriteOfEntity; }
  sf::Vector2f VirtualEntity::getSpaceShipPosition() { return sf::Vector2f(POS.x, POS.y); }
  short* VirtualEntity::getLife() { return &EntityLife; }

  void VirtualEntity::centerInWindow(sf::Vector2f WindowSize) {
    POS.y = WindowSize.y / 2;
    POS.x = WindowSize.x / 2;
  }
  void VirtualEntity::scaleSpaceShip(int scx, int scy) { SpriteOfEntity.setScale(scx, scy); }

}  // namespace MatthewsNamespace