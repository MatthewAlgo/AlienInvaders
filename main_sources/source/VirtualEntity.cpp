#include "alieninvadersretro/VirtualEntity.h"
/*
  Here we implement the class related to the entity, a virtual class that will be inherited by the
  elements that move on the screen
*/

namespace GameNamespace {
  VirtualEntity::VirtualEntity(sf::Vector2f WindowSize, sf::Texture Texture)
      : WinSize(WindowSize), TextureOfEntity(Texture) {
    POS.y = WindowSize.y / 2;
    POS.x = WindowSize.x / 2;
    // Set the position of the spaceship
    SpriteOfEntity.setTexture(TextureOfEntity);
    SpriteOfEntity.setPosition(sf::Vector2f(POS.x, POS.y));
  }

  VirtualEntity::VirtualEntity(sf::Vector2f WindowSize) {
    POS.y = WindowSize.y / 2;
    POS.x = WindowSize.x / 2;
    SpriteOfEntity.setPosition(sf::Vector2f(POS.x, POS.y));
  }

  VirtualEntity::VirtualEntity() {}

  // Movement functions
  void VirtualEntity::MoveUp(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) {
    POS.y -= amount;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  void VirtualEntity::MoveDown(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) {
    POS.y += amount;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  void VirtualEntity::MoveLeft(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) {
    POS.x -= amount;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  void VirtualEntity::MoveRight(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT) {
    POS.x += amount;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

  void VirtualEntity::setTexture(sf::Texture& texture) {
    TextureOfEntity = texture;
    SpriteOfEntity.setTexture(TextureOfEntity);
  }  // Plus Sprite

  void VirtualEntity::setTexture(std::string FileName) {
    TextureOfEntity.loadFromFile(FileName);
    SpriteOfEntity.setTexture(TextureOfEntity);
  }  // Plus Sprite
 
  void VirtualEntity::setSprite(sf::Sprite& sprite) { SpriteOfEntity = sprite; }
  void VirtualEntity::setPosition(double X, double Y) { 
      POS.x = X;
      POS.y = Y;
      SpriteOfEntity.setPosition(POS.x, POS.y); 
  }
  void VirtualEntity::setLife(short L) { this->EntityLife = L;}
  void VirtualEntity::centerInWindow(sf::Vector2f WindowSize) {
    POS.y = WindowSize.y / 2;
    POS.x = WindowSize.x / 2;
  }

  sf::Texture* VirtualEntity::getTexture() { return &this->TextureOfEntity; }

  sf::Sprite* VirtualEntity::getSprite() { return &SpriteOfEntity; }

  sf::Vector2f VirtualEntity::getPosition() {
    return sf::Vector2f(POS.x, POS.y);
  }

  void VirtualEntity::setMainWindowSize(int X, int Y) {}

  short VirtualEntity::getLife() { return this->EntityLife; }


  void VirtualEntity::scaleEntity(double scx, double scy) {
    SpriteOfEntity.setScale((double)scx, (double)scy);
  }

}  // namespace GameNamespace