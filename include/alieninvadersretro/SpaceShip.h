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
#  include "Constants.h"

#  pragma region SPACESHIP_CLASS
namespace GameNamespace {
  class SpaceShip : public virtual VirtualEntity {
  private:
    
    short Life = Constants::INITIAL_PLAYER_LIFE;
    long long PlayerScore = Constants::INITIAL_PLAYER_SCORE;  // Player Score is set to zero

  public:
    // Each spaceship has a queue of bullets
    std::deque<std::shared_ptr<SpaceShipBullet>> BulletDeque;
    sf::Vector2f window_size_;

    // The spaceship moves according to the VirtualEntity

    // Constructors
    SpaceShip(sf::Vector2f WindowSize, sf::Texture Texture) {
      WinSize = WindowSize;
      TextureOfEntity = Texture;
      VirtualEntity(WindowSize, Texture);
    }
    SpaceShip(sf::Vector2f WindowSize) : window_size_(WindowSize) {
      // Init the explosion if this constructor is called
      WinSize = WindowSize;
      VirtualEntity(Winsize);
    }

    SpaceShip() : VirtualEntity() {}
    ~SpaceShip() = default;

    void setTexture(sf::Texture& texture) override final;
    void setSprite(sf::Sprite& sprite) override final;
    void setPosition(double X, double Y) override final;

    void Shoot(int PlayerScore);
    int IterateThroughBullets(
        sf::RenderWindow* WINDOW,
        std::vector<std::unique_ptr<EnemySpaceShip>>&
            Enemies);  // Keep a vector of bullets coming from the other enemies
    void FreeUpMemoryBullets();
  };
}  // namespace GameNamespace
#  pragma endregion SPACESHIP_CLASS
#endif