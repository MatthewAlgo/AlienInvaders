#include "alieninvadersretro/AnimationWindow.h"
#include "alieninvadersretro/BoomBox.h"
#include "alieninvadersretro/SpaceShip.h"

namespace GameNamespace {
  void GameNamespace::SpaceShip::Shoot(int PlayerScore) {
    // Load the bullet -> The bullet receives some speed of +10 per frame
    // The initial bullet / shuttle
    std::shared_ptr<SpaceShipBullet> CurrentBullet = std::make_shared<SpaceShipBullet>();
    if (PlayerScore < 50'000) {
      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x + 13, POS.y - 40);  // Front Bullet
    } else if (PlayerScore >= 50'000 && PlayerScore < 100'000) {
      // Side bullets upgrade
      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x, POS.y - 40);

      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x + 26, POS.y - 40);
    } else {
      // Triple shot
      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x, POS.y - 40);

      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x + 26, POS.y - 40);

      BulletDeque.push_back(std::make_shared<SpaceShipBullet>(*CurrentBullet));
      BulletDeque.back()->setTexture("NeonVertical.png");
      BulletDeque.back()->scaleEntity(0.25, 0.25);
      BulletDeque.back()->setPosition(POS.x + 13, POS.y - 40);  // Front Bullet
    }
  }

  int GameNamespace::SpaceShip::IterateThroughBullets(sf::RenderWindow* WINDOW,
                                                          std::vector<std::unique_ptr<EnemySpaceShip>>& Enemies) {
    int scoreByPlayer = 0;
    for (int i{}; i < this->BulletDeque.size(); ++i) {
      WINDOW->draw(*this->BulletDeque[i]->getSprite());
      if (this->BulletDeque.at(i) != nullptr) {
        this->BulletDeque[i]->setPosition(
            this->BulletDeque[i]->getPosition().x,
            this->BulletDeque[i]->getPosition().y - 45);
      }
    }
    // Check if the bullets hit enemy spaceships
    for (int i{}; i < BulletDeque.size(); ++i) {
      // Iterate through enemies and their positions
      for (int j{}; j < Enemies.size(); ++j) {
        if (BulletDeque.at(i)->getPosition().x
                > Enemies.at(j)->getPosition().x - 40
            && BulletDeque.at(i)->getPosition().x
                   < Enemies.at(j)->getPosition().x + 20)
          if (BulletDeque.at(i)->getPosition().y
                  > Enemies.at(j)->getPosition().y - 40
              && BulletDeque.at(i)->getPosition().y
                     < Enemies.at(j)->getPosition().y + 20) {
            // Draw Explosion on Impact
            ExplosionSprite.setPosition(BulletDeque.at(i)->getPosition().x,
                                        BulletDeque.at(i)->getPosition().y);
            WINDOW->draw(ExplosionSprite);
            scoreByPlayer++;
            // Decrease life + set death behavior
            Enemies.at(j)->setLife(Enemies.at(j)->getLife() - BulletDeque.at(i)->getDamage());
            if (Enemies.at(j)->getLife() + EnemySpaceShip::LIFE_SUPPLIER == 0) {
              BoomBox::WindowCollisionEffect();  // Will generate a collision sound effect
              Enemies.at(j)->Die();
              // EnemySpaceShip* Iterator = Enemies.at(j).get();
              // delete Iterator;
              Enemies.erase(Enemies.begin() + j);
            }
            if (this->BulletDeque.at(i) != NULL) {
              // We delete the bullet and deliver damage to the main space shuttle
              // SpaceShipBullet* it = this->BulletDeque.at(i).get();
              // delete it;
              // it = nullptr;
              this->BulletDeque.erase(this->BulletDeque.begin() + i);
            }
            break;  // Exit the loop so that variables are updated -> Seems to be time consuming
          }
      }
    }
    return scoreByPlayer * 100;
  }
  void GameNamespace::SpaceShip::FreeUpMemoryBullets() {
    for (unsigned int i{}; i < this->BulletDeque.size(); i++) {  // Manage and free up the memory
      if (this->BulletDeque.at(i)->getPosition().y
          < -300) {  // If the bullet is offscreen
        // SpaceShipBullet* it = this->BulletDeque.at(i).get();
        // delete it;
        // it = nullptr;
        this->BulletDeque.erase(this->BulletDeque.begin() + i);
      }
    }
  }

  // Functions initially placed inside the header file
  void SpaceShip::setTexture(sf::Texture& texture) { TextureOfEntity = texture; }
  void SpaceShip::setSprite(sf::Sprite& sprite) { SpriteOfEntity = sprite; }
  void SpaceShip::setPosition(double X, double Y) {
    POS.x = X;
    POS.y = Y;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }

}  // namespace GameNamespace