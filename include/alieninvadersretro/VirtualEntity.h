#pragma once
#ifndef V_ENTITY_H
#  define V_ENTITY_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>

enum entity_type { PLAYER, ENEMY, BULLET };  // Each entity has a type
enum entity_movement_speed {
  ENTITY_MOVEMENT_SPEED_DEFAULT = 30,
  ENTITY_MOVEMENT_SPEED_FAST = 60,
  ENTITY_MOVEMENT_SPEED_SLOW = 15
};
enum entity_life { ENTITY_LIFE_DEFAULT = 10, ENTITY_LIFE_MORE = 20, ENTITY_LIFE_LESS = 5 };

/*
 This class defines a base entity, a thing that can move and has a life and a position, a texture
 and a sprite
*/

#  pragma region V_CLASS_ENTITY
namespace GameNamespace {
  class VirtualEntity {
  private:
    short EntityLife = ENTITY_LIFE_DEFAULT;  // Each entity has a life
  protected:
    struct Position {
      double x, y, speed = 0;
    };
    Position POS;  // Each entity has a position

    sf::Texture TextureOfEntity;
    sf::Sprite SpriteOfEntity;
    sf::Vector2f WinSize;  // Size of the window in which the entity is located

    // It produces explosions on its bullet collisions -> their data is located here
    sf::Texture Explosion;
    sf::Sprite ExplosionSprite;

    int type = PLAYER;     // Each entity has a type, by default it is player

  public:
    // Constructors
    VirtualEntity(sf::Vector2f WindowSize, sf::Texture Texture);
    VirtualEntity(sf::Vector2f WindowSize);
    VirtualEntity();

    virtual ~VirtualEntity() = default;  // Default destructor

    // FUNCTIONS - EACH ENTITY CAN MOVE
    virtual void MoveUp(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT);
    virtual void MoveDown(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT);
    virtual void MoveLeft(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT);
    virtual void MoveRight(int amount = ENTITY_MOVEMENT_SPEED_DEFAULT);

    // Setters
    virtual void setTexture(sf::Texture& texture);  // Pure virtual functions
    virtual void setSprite(sf::Sprite& sprite);
    virtual void setTexture(std::string FileName);
    virtual void setPosition(double X, double Y);
    virtual void setLife(short L);

    // Modifiers
    virtual void centerInWindow(sf::Vector2f WindowSize);
    virtual void scaleEntity(double scx, double scy);

    // Getters
    virtual sf::Texture* getTexture();
    virtual sf::Sprite* getSprite();
    virtual sf::Vector2f getPosition();
    virtual void setMainWindowSize(int X, int Y);
    virtual short getLife();
  };
}

#endif