#pragma once
#ifndef ENEMY_SPACE_SHIP_H
#  define ENEMY_SPACE_SHIP_H

#  include <SFML/Graphics.hpp>
#  include <SFML/Window.hpp>
#  include <deque>

#  include "EnemySpaceShipBullet.h"
#  include "BoomBox.h"
#  include "SpaceShip.h"
#  include "VirtualSpaceShip.h"

#  pragma region ENEMY_SPACESHIP_REGION
namespace GameNamespace {
  class EnemySpaceShip : public virtual VirtualSpaceShip {
  private:
    short Life = 10; // The enemies have reduced life
  protected:
    int shooter_clock = 0;
  public:
    // Each spaceship has a queue of bullets
    std::deque<std::unique_ptr<EnemySpaceShipBullet>> BulletDeque;
    static int LIFE_SUPPLIER;

    inline void MoveUp(int) override final;
    inline void MoveDown(int) override final;
    inline void MoveLeft(int) override final;
    inline void MoveRight(int) override final;

    EnemySpaceShip(sf::Vector2f WindowSize, sf::Texture Texture, int WWidth);
    EnemySpaceShip(sf::Vector2f WindowSize);
    EnemySpaceShip();
    ~EnemySpaceShip() = default;
    
    void setTexture(std::string FileName) {
      TextureOfEntity.loadFromFile(FileName);
      SpriteOfEntity.setTexture(TextureOfEntity);
    }
  
    void Shoot();
    void GenerateInDrawFunctionOfMainWindow(sf::RenderWindow* Window,
                                            std::string SpaceShipTextureName);
    void DrawBulletsInWindow(sf::RenderWindow* Window, std::vector<SpaceShip*>);
    void FreeUpMemoryFromBullets(sf::RenderWindow* Window);
    void Draw_IterateExistingItem(sf::RenderWindow* Window);
    void MoveRandomLeftOrRightorUpOrDown();
    void Die();  // Free up the buffer of bullets
  };

}  // namespace GameNamespace
#  pragma endregion ENEMY_SPACESHIP_REGION

#endif
