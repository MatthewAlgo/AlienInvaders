#pragma once
#ifndef VIRTUAL_ENTITY_HEADER_H
#  define VIRTUAL_ENTITY_HEADER_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <deque>
#  include <vector>

// #  include "EnemySpaceShip.h" -> Careful at circular dependencies!
#  include "SpaceShipBullet.h"

#  pragma region V_CLASS_ENTITY
namespace MatthewsNamespace {
  class VirtualEntity {
  private:
      short EntityLife = 10; // Each entity has a life
  protected:
    typedef struct Position {
      double x, y, speed = 0;
    };
    Position POS;  // Each entity has a position

    sf::Texture TextureOfEntity;
    sf::Sprite SpriteOfEntity;
    sf::Vector2f WinSize;

    // It produces explosions on its bullet collisions -> their data is located here
    sf::Texture Explosion;
    sf::Sprite ExplosionSprite;

  public:
    // Constructors
    VirtualEntity(sf::Vector2f WindowSize, sf::Texture Texture);
    VirtualEntity(sf::Vector2f WindowSize);
    VirtualEntity();
    
    virtual ~VirtualEntity() = default;        // Default destructor


    std::deque<SpaceShipBullet*> BulletDeque;  // Each entity has its own stack of bullets

    // FUNCTIONS - EACH ENTITY CAN MOVE
    inline virtual void MoveUp();
    inline virtual void MoveDown();
    inline virtual void MoveLeft();
    inline virtual void MoveRight();


    // Setters
    virtual void setTexture(sf::Texture& texture); // Pure virtual functions
    virtual void setSprite(sf::Sprite& sprite);
    virtual void setSpaceShipPosition(double X, double Y);
    virtual void setLife(short L);
    virtual void setMainWindowSize(int X, int Y);

    // Modifiers
    virtual void centerInWindow(sf::Vector2f WindowSize);
    virtual void scaleSpaceShip(int scx, int scy);

    // Getters
    virtual sf::Texture* getSpaceShipTexture();
    virtual sf::Sprite* getSpaceShipSprite();
    virtual sf::Vector2f getSpaceShipPosition();
    virtual short* getLife();

  };
}  // namespace MatthewsNamespace
#  pragma endregion V_CLASS_ENTITY

#endif