#include "alieninvadersretro/EnemySpaceShip.h"

int MatthewsNamespace::EnemySpaceShip::LIFE_SUPPLIER = 0;

namespace MatthewsNamespace {
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
    this->setSpaceShipPosition(
        MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0, WWidth), 0);

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


  inline void EnemySpaceShip::MoveUp() {
    if (POS.y - 5 > 0 && POS.y - 5 < WinSize.y) POS.y -= 5;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void EnemySpaceShip::MoveDown() {
    if (POS.y + 5 > 0 && POS.y + 5 < WinSize.y) POS.y += 5;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void EnemySpaceShip::MoveLeft() {
    if (POS.x - 5 > 0 && POS.x - 5 < WinSize.y) POS.x -= 5;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
  inline void EnemySpaceShip::MoveRight() {
    if (POS.x + 5 > 0 && POS.x + 5 < WinSize.y) POS.x += 5;
    SpriteOfEntity.setPosition(POS.x, POS.y);
  }
}  // namespace MatthewsNamespace

void MatthewsNamespace::EnemySpaceShip::Shoot() {
  shooter_clock++;
  if (shooter_clock % 100 == 0) {
    // Load the bullet -> The bullet receives some speed of +10 per frame
    std::unique_ptr<EnemySpaceShipBullet> CurrentBullet =
        std::make_unique<EnemySpaceShipBullet>();
    BulletDeque.push_back(CurrentBullet);

    BulletDeque.back()->setTexture("NeonVertical.png");
    BulletDeque.back()->scaleSpaceShipBullet(0.4, 0.2);
    BulletDeque.back()->getSpaceShipBulletSprite()->setColor(sf::Color::Yellow);
    BulletDeque.back()->setSpaceShipBulletPosition(POS.x - 13, POS.y + 10);  // Front Bullet
    shooter_clock = MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0, 50);
    BoomBox::ShootSoundEffect();  // Sound Effect
  }
}

void MatthewsNamespace::EnemySpaceShip::GenerateInDrawFunctionOfMainWindow(
    sf::RenderWindow* Window, std::string SpaceShipTextureName) {
  // Generate a new spaceship
  this->setSpaceShipPosition(
      MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0,
                                                                              Window->getSize().x),
      -20);  // Spawn with offset so that enemies appear fluently on screen
  this->setTexture(SpaceShipTextureName);
  this->getSpaceShipSprite()->setScale(0.1, 0.1);
  Window->draw(*this->getSpaceShipSprite());
  this->POS.speed = 0.5;
}
void MatthewsNamespace::EnemySpaceShip::DrawBulletsInWindow(sf::RenderWindow* Window, int XSSPos,
                                                            int YSSPos, short& SS) {
  for (int i{}; i < BulletDeque.size(); ++i) {
    Window->draw(*this->BulletDeque[i]->getSpaceShipBulletSprite());
    if (this->BulletDeque.at(i) != nullptr) {
      this->BulletDeque[i]->setSpaceShipBulletPosition(
          this->BulletDeque[i]->getSpaceShipBulletPosition().x,
          this->BulletDeque[i]->getSpaceShipBulletPosition().y + 10);  // Bullet Speed
    }
  }
  // Check if the bullets hit the spaceship
  for (int i{}; i < BulletDeque.size(); ++i) {
    if (BulletDeque.at(i)->getSpaceShipBulletPosition().x > XSSPos - 40
        && BulletDeque.at(i)->getSpaceShipBulletPosition().x < XSSPos + 40)
      if (BulletDeque.at(i)->getSpaceShipBulletPosition().y > YSSPos - 40
          && BulletDeque.at(i)->getSpaceShipBulletPosition().y < YSSPos + 80) {
        // Draw Explosion on Impact
        Explosion.loadFromFile("Explosion.png");
        ExplosionSprite.setTexture(Explosion);
        ExplosionSprite.setScale(0.1, 0.1);
        ExplosionSprite.setPosition(BulletDeque.at(i)->getSpaceShipBulletPosition().x,
                                    BulletDeque.at(i)->getSpaceShipBulletPosition().y);
        Window->draw(ExplosionSprite);     // Will output a white square -> Retro style explosion
        BoomBox::WindowCollisionEffect();  // Will generate a collision sound effect

        SS--;
        SS -= EnemySpaceShipBullet::DAMAGE_SUPPLIER;
        if (SS <= 0) {
          BoomBox::GameOverEffect();
          SS = 0;
        }
        // The Player Died
        // Show game over screen or whatever

        // We delete the bullet and deliver damage to the main space shuttle
        // EnemySpaceShipBullet* it = this->BulletDeque.at(i).get();
        // delete it;
        // it = nullptr;
        this->BulletDeque.erase(this->BulletDeque.begin() + i);
      }
  }
}

void MatthewsNamespace::EnemySpaceShip::FreeUpMemoryFromBullets(sf::RenderWindow* Window) {
  for (unsigned int i{}; i < this->BulletDeque.size(); i++) {  // Manage and free up the memory
    if (this->BulletDeque.at(i)->getSpaceShipBulletPosition().y
        > Window->getSize().y) {  // If the bullet is offscreen
      // EnemySpaceShipBullet* it = this->BulletDeque.at(i).get();
      // delete it;
      // it = nullptr;
      this->BulletDeque.erase(this->BulletDeque.begin() + i);
    }
  }
}
void MatthewsNamespace::EnemySpaceShip::Draw_IterateExistingItem(sf::RenderWindow* Window) {
  POS.y += this->POS.speed;
  MoveRandomLeftOrRightorUpOrDown();
  this->setSpaceShipPosition(POS.x, POS.y);
  this->getSpaceShipSprite()->setScale(0.1, 0.1);
  Window->draw(*this->getSpaceShipSprite());
}
void MatthewsNamespace::EnemySpaceShip::MoveRandomLeftOrRightorUpOrDown() {
  int randomx = MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(-10, 10);
  int randomy = MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(-10, 10);

  if (POS.x + randomx > 0 && POS.x + randomx < WinSize.x) POS.x += randomx;
  if (POS.y + randomy > -20 && POS.y + randomy < WinSize.x) POS.y += randomy;
}
void MatthewsNamespace::EnemySpaceShip::Die() {                // Free up the buffer of bullets
  for (unsigned int i{}; i < this->BulletDeque.size(); i++) {  // Manage and free up the memory
    // EnemySpaceShipBullet* it = this->BulletDeque.at(i).get();
    // delete it;
    // it = nullptr;
    this->BulletDeque.erase(this->BulletDeque.begin() + i);
  }
}