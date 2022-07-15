#pragma once
#ifndef SPACESHIP_H
#  define SPACESHIP_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <deque>
#  include <vector>

#  include "EnemySpaceShip.h"
#  include "SpaceShipBullet.h"
#  include "VirtualEntity.h"

#  pragma region SPACESHIP_CLASS
namespace MatthewsNamespace {
  class SpaceShip : public virtual VirtualEntity {
  public:
    short Life = 50;
    // Each spaceship has a queue of bullets
    std::deque<std::unique_ptr<SpaceShipBullet>> BulletDeque;
    
    // The spaceship moves according to the VirtualEntity

    // Constructors
    SpaceShip(sf::Vector2f WindowSize, sf::Texture Texture) {
      WinSize = WindowSize;
      TextureOfEntity=Texture;
      VirtualEntity(WindowSize, Texture);

    }
    SpaceShip(sf::Vector2f WindowSize) {
      // Init the explosion if this constructor is called
      WinSize=WindowSize;
      VirtualEntity(Winsize);
    }
    SpaceShip() : VirtualEntity(){}
    ~SpaceShip() = default;

    void setTexture(sf::Texture& texture) override;
    void setSprite(sf::Sprite& sprite) override;
    void setSpaceShipPosition(double X, double Y) override;
    void setLife(short L) override;
    void setMainWindowSize(int X, int Y) override;

    
    sf::Texture* getSpaceShipTexture() override;
    sf::Sprite* getSpaceShipSprite() override;
    sf::Vector2f getSpaceShipPosition() override;
    short* getLife() override;
  

    void centerInWindow(sf::Vector2f WindowSize) override;
    void scaleSpaceShip(int scx, int scy) override;
    void Shoot(int PlayerScore);
    int IterateThroughBullets(sf::RenderWindow* WINDOW, std::vector<std::unique_ptr<EnemySpaceShip>>& Enemies);
    void FreeUpMemoryBullets();

  };
}  // namespace MatthewsNamespace
#  pragma endregion SPACESHIP_CLASS
#endif