#pragma once
#ifndef RANDOM_PARTICLES_GEN_H
#  define RANDOM_PARTICLES_GEN_H

#  include <SFML/Graphics.hpp>
#  include <SFML/Window.hpp>
#  include <random>
#  include <vector>

#  pragma region RANDOM_PG_CLASS
namespace MatthewsNamespace {
  class RandomParticlesGenerator {
  private:
    struct WhiteParticle {
      double x, y = 0;
      std::unique_ptr<sf::Texture> Texture;
      sf::Sprite Sprite;
      double speed;
    };
    unsigned short generator_clock = 0;
    std::vector<std::unique_ptr<WhiteParticle>> VectorOfParticles;

  public:
    RandomParticlesGenerator() = default;
    ~RandomParticlesGenerator() = default;

    static int Mersenne_Twister_Generator(int minvalue, int maxvalue) {
      std::random_device device;
      std::mt19937 generator(device());
      std::uniform_int_distribution<int> distribution(minvalue, maxvalue);
      return distribution(generator);
    }
    void Generate() {
      generator_clock++;
      if (generator_clock % 2 == 0) {
        std::unique_ptr<WhiteParticle> Xparticle = std::make_unique<WhiteParticle>();
        std::unique_ptr<sf::Texture> Texture = std::make_unique<sf::Texture>();
        Texture->loadFromFile("WhiteDot.png");
        VectorOfParticles.push_back(std::move(Xparticle));
        VectorOfParticles.back()->speed = Mersenne_Twister_Generator(5, 20);
        VectorOfParticles.back()->x = Mersenne_Twister_Generator(0, 1000);
        VectorOfParticles.back()->Texture = std::move(Texture);
        VectorOfParticles.back()->Sprite.setTexture(*VectorOfParticles.back()->Texture);
        VectorOfParticles.back()->Sprite.setScale(0.01, 0.01);
        VectorOfParticles.back()->Sprite.setPosition(sf::Vector2f(VectorOfParticles.back()->x, 0));
        generator_clock = 0;
      }
    }

    void InLoopForParticles(sf::RenderWindow* X) {
      for (int i{}; i < VectorOfParticles.size(); ++i) {
        X->draw(VectorOfParticles.at(i)->Sprite);
        VectorOfParticles.at(i)->y += VectorOfParticles.at(i)->speed;
        VectorOfParticles.at(i)->Sprite.setPosition(
            sf::Vector2f(VectorOfParticles.at(i)->x, VectorOfParticles.at(i)->y));
      }
    }
    void ClearMemory(sf::RenderWindow* X) {
      for (int i{}; i < VectorOfParticles.size(); ++i) {
        if (VectorOfParticles.at(i)->y > X->getSize().y) {
          // delete VectorOfParticles.at(i)->Texture;
          // WhiteParticle* it = VectorOfParticles.at(i);
          // delete it;
          // it = nullptr;
          VectorOfParticles.erase(VectorOfParticles.begin() + i);
        }
      }
    }
  };
}  // namespace MatthewsNamespace
#  pragma endregion RANDOM_PG_CLASS
#endif
