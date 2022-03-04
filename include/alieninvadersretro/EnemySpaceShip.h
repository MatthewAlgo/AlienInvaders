#pragma once
#ifndef ENEMY_SPACE_SHIP_H
#  define ENEMY_SPACE_SHIP_H

#  include <SFML/Graphics.hpp>
#  include <SFML/Window.hpp>
#  include <deque>

#  include "EnemySpaceShipBullet.h"
#  include "BoomBox.h"
#  include "VirtualEntity.h"

#  pragma region ENEMY_SPACESHIP_REGION
namespace MatthewsNamespace {
  class EnemySpaceShip : public virtual VirtualEntity {
  private:
    short Life = 10; // The enemies have reduced life
  protected:
    int shooter_clock = 0;
  public:
    // Each spaceship has a queue of bullets
    std::deque<EnemySpaceShipBullet*> BulletDeque;
    static int LIFE_SUPPLIER;

    inline void MoveUp() override;
    inline void MoveDown() override;
    inline void MoveLeft() override;
    inline void MoveRight() override;

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
    void DrawBulletsInWindow(sf::RenderWindow* Window, int XSSPos, int YSSPos, short& SS);
    void FreeUpMemoryFromBullets(sf::RenderWindow* Window);
    void Draw_IterateExistingItem(sf::RenderWindow* Window);
    void MoveRandomLeftOrRightorUpOrDown();
    void Die();  // Free up the buffer of bullets
  };

}  // namespace MatthewsNamespace
#  pragma endregion ENEMY_SPACESHIP_REGION

#endif
