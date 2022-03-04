#pragma once
#ifndef SPACE_SHIP_BULLET_H
#  define SPACE_SHIP_BULLET_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>

namespace MatthewsNamespace {
  class SpaceShipBullet {
  protected:
    typedef struct Position {
      double x, y;
    };
    Position POS;

    sf::Texture TextureOfSpaceShipBullet;
    sf::Sprite SpriteOfSpaceShipBullet;
    sf::Vector2f WinSize;

    unsigned int DAMAGE = 1;

  public:
    SpaceShipBullet(sf::Vector2f WindowSize, sf::Texture Texture)
        : WinSize(WindowSize), TextureOfSpaceShipBullet(Texture) {
      POS.y = WindowSize.y / 2;
      POS.x = WindowSize.x / 2;
      // Set the position of the spaceship
      SpriteOfSpaceShipBullet.setTexture(TextureOfSpaceShipBullet);
      SpriteOfSpaceShipBullet.setPosition(sf::Vector2f(POS.x, POS.y));
    }
    SpaceShipBullet() = default;
    ~SpaceShipBullet() = default;

    inline void MoveUp() {
      POS.y -= 30;
      SpriteOfSpaceShipBullet.setPosition(POS.x, POS.y);
    }

    void setTexture(sf::Texture& texture) {
      TextureOfSpaceShipBullet = texture;
      SpriteOfSpaceShipBullet.setTexture(TextureOfSpaceShipBullet);
    }  // Plus Sprite
    void setTexture(std::string FileName) {
      TextureOfSpaceShipBullet.loadFromFile(FileName);
      SpriteOfSpaceShipBullet.setTexture(TextureOfSpaceShipBullet);
    }  // Plus Sprite
    void setSprite(sf::Sprite& sprite) { SpriteOfSpaceShipBullet = sprite; }
    void centerInWindow(sf::Vector2f WindowSize) {
      POS.y = WindowSize.y / 2;
      POS.x = WindowSize.x / 2;
    }
    void setSpaceShipBulletPosition(double X, double Y) {
      POS.x = X;
      POS.y = Y;
      SpriteOfSpaceShipBullet.setPosition(POS.x, POS.y);
    }
    void scaleSpaceShipBullet(double scx, double scy) {
      SpriteOfSpaceShipBullet.setScale((double)scx, (double)scy);
    }

    sf::Texture* getSpaceShipBulletTexture() { return &TextureOfSpaceShipBullet; }
    sf::Sprite* getSpaceShipBulletSprite() { return &SpriteOfSpaceShipBullet; }
    sf::Vector2f getSpaceShipBulletPosition() { return sf::Vector2f(POS.x, POS.y); }
    unsigned int* getDamage() { return &DAMAGE; }
  };
}  // namespace MatthewsNamespace
#endif