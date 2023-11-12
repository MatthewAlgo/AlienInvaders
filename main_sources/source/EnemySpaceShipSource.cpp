#include "alieninvadersretro/EnemySpaceShip.h"
#include "alieninvadersretro/SpaceShip.h" // Include the spaceship class, basically this gets included if the 

int GameNamespace::EnemySpaceShip::LIFE_SUPPLIER = 0;

namespace GameNamespace {
  // CONSTRUCTOR DEFINITION
  EnemySpaceShip::EnemySpaceShip(sf::Vector2f WindowSize, sf::Texture Texture, int WWidth) {
    // This constructor initiates in a different way - only methods from base class will be
    // overriden
    WinSize = WindowSize;
    TextureOfEntity = Texture;
    // POS.y = WindowSize.y / 2;
    POS.x = 0;
    // Set the position of the spaceship
    SpriteOfEntity.setTexture(TextureOfEntity);
    this->setPosition(
        GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0, WWidth), 0);

    // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  };
  EnemySpaceShip::EnemySpaceShip(sf::Vector2f WindowSize) {  // Init the explosion if this constructor is called
    WinSize = WindowSize;
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  };
  EnemySpaceShip::EnemySpaceShip() {  // Init the explosion if this constructor is called
    Explosion.loadFromFile("Explosion.png");
    ExplosionSprite.setTexture(Explosion);
    ExplosionSprite.setScale(0.1, 0.1);
  };
}  // namespace GameNamespace

void GameNamespace::EnemySpaceShip::Shoot() {
  shooter_clock++;
  if (shooter_clock % 100 == 0) {
    // Load the bullet -> The bullet receives some speed of +10 per frame
    std::unique_ptr<EnemySpaceShipBullet> CurrentBullet =
        std::make_unique<EnemySpaceShipBullet>();
    BulletDeque.push_back(std::move(CurrentBullet));

    BulletDeque.back()->setTexture("NeonVertical.png");
    BulletDeque.back()->scaleEntity(0.4, 0.2);
    BulletDeque.back()->getSprite()->setColor(sf::Color::Yellow);
    BulletDeque.back()->setPosition(POS.x - 13, POS.y + 10);  // Front Bullet
    shooter_clock = GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0, 50);
    BoomBox::ShootSoundEffect();  // Sound Effect
  }
}

void GameNamespace::EnemySpaceShip::GenerateInDrawFunctionOfMainWindow(
    sf::RenderWindow* Window, std::string SpaceShipTextureName) {
  // Generate a new spaceship
  this->setPosition(
      GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0,
                                                                              Window->getSize().x),
      -20);  // Spawn with offset so that enemies appear fluently on screen
  this->setTexture(SpaceShipTextureName);
  this->getSprite()->setScale(0.1, 0.1);
  Window->draw(*this->getSprite());
  this->POS.speed = 0.5;
}
void GameNamespace::EnemySpaceShip::DrawBulletsInWindow(sf::RenderWindow* Window, std::vector<SpaceShip*> playerSpaceShips) {
  for (int i{}; i < BulletDeque.size(); ++i) {
    Window->draw(*this->BulletDeque[i]->getSprite());
    if (this->BulletDeque.at(i) != nullptr) {
      this->BulletDeque[i]->setPosition(
          this->BulletDeque[i]->getPosition().x,
          this->BulletDeque[i]->getPosition().y + 10);  // Bullet Speed
    }
  }
  // Check if the bullets hit the spaceship
  // Iterate through the spaceships and check if a bullet hits the spaceship
  for (auto spaceShipIterator : playerSpaceShips) {
    for (int i{}; i < BulletDeque.size(); ++i) {
      if (BulletDeque.at(i)->getPosition().x > spaceShipIterator->getPosition().x - 40
          && BulletDeque.at(i)->getPosition().x < spaceShipIterator->getPosition().x + 40)
        if (BulletDeque.at(i)->getPosition().y > spaceShipIterator->getPosition().y - 40
            && BulletDeque.at(i)->getPosition().y < spaceShipIterator->getPosition().y + 80) {
          // Draw Explosion on Impact
          Explosion.loadFromFile("Explosion.png");
          ExplosionSprite.setTexture(Explosion);
          ExplosionSprite.setScale(0.1, 0.1);
          ExplosionSprite.setPosition(BulletDeque.at(i)->getPosition().x,
                                      BulletDeque.at(i)->getPosition().y);
          Window->draw(ExplosionSprite);     // Will output a white square -> Retro style explosion
          BoomBox::WindowCollisionEffect();  // Will generate a collision sound effect

          spaceShipIterator->setLife(spaceShipIterator->getLife() - 1);
          spaceShipIterator->setLife(spaceShipIterator->getLife()
                                     - EnemySpaceShipBullet::DAMAGE_SUPPLIER);
          if (spaceShipIterator->getLife() <= 0) {
            BoomBox::GameOverEffect();
            spaceShipIterator->setLife(0); // Set the life as 0, because we constantly subtract from it, at some point the life can become a nonnegative
          }
          // The Player Died
          // Show game over screen
          this->BulletDeque.erase(this->BulletDeque.begin() + i);
        }
    }
  }
}

void GameNamespace::EnemySpaceShip::FreeUpMemoryFromBullets(sf::RenderWindow* Window) {
  for (unsigned int i{}; i < this->BulletDeque.size(); i++) {  // Manage and free up the memory
    if (this->BulletDeque.at(i)->getPosition().y
        > Window->getSize().y) {  // If the bullet is offscreen
      // Memory managed by smart pointers?
      // EnemySpaceShipBullet* it = this->BulletDeque.at(i).get();
      // delete it;
      // it = nullptr;
      this->BulletDeque.erase(this->BulletDeque.begin() + i);
    }
  }
}
void GameNamespace::EnemySpaceShip::Draw_IterateExistingItem(sf::RenderWindow* Window) {
  POS.y += this->POS.speed;
  MoveRandomLeftOrRightorUpOrDown();
  this->setPosition(POS.x, POS.y);
  this->getSprite()->setScale(0.1, 0.1);
  Window->draw(*this->getSprite());
}
void GameNamespace::EnemySpaceShip::MoveRandomLeftOrRightorUpOrDown() {
  int randomx = GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(-10, 10);
  int randomy = GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(-10, 10);

  if (POS.x + randomx > 0 && POS.x + randomx < WinSize.x) POS.x += randomx;
  if (POS.y + randomy > -20 && POS.y + randomy < WinSize.x) POS.y += randomy;
}
void GameNamespace::EnemySpaceShip::Die() {                // Free up the buffer of bullets
  for (unsigned int i{}; i < this->BulletDeque.size(); i++) {  // Manage and free up the memory
    // EnemySpaceShipBullet* it = this->BulletDeque.at(i).get();
    // delete it;
    // it = nullptr;
    this->BulletDeque.erase(this->BulletDeque.begin() + i);
  }
}