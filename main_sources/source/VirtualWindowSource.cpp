#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "alieninvadersretro/VirtualWindow.h"

#pragma region VIRTCLASS_FUNC_IMPLEMENTATIONS
void GameNamespace::VirtualWindowClass::MainWindowThreadExecution(
    TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) {
  sf::WindowHandle handle
      = ITEM_HOLDER.getA()->getSystemHandle();  // Use the handle with OS specific functions
  // Main Window Settings
  ITEM_HOLDER.getA()->setActive(true);
  ITEM_HOLDER.getA()->setVerticalSyncEnabled(true);
  ITEM_HOLDER.getA()->setFramerateLimit(60);
  std::unique_ptr<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>> CurrentHolder
      = std::make_unique<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>>(WindowPointer.get(),
                                                                                 this);
  RenderTextures(*CurrentHolder.get());
  //////// Temporary - work in progress

  // Display main Window
  while (ITEM_HOLDER.getA()->isOpen()) {
    sf::Event* Event = new sf::Event();
    while (ITEM_HOLDER.getA()->pollEvent(*Event)) {
      if (Event->type == sf::Event::Closed) {
        sf::sleep(sf::Time(sf::seconds(1)));  // Sleep for 1s
        // delete this->ParticleGenerator.get();       // Delete the random particles generator
        ITEM_HOLDER.getA()->close();          // Deletes the animation window
        exit(EXIT_SUCCESS);
      } else if (Event->type == sf::Event::KeyPressed) {
        if (Event->key.code == sf::Keyboard::Escape) {  // Exits on ESC pressed

          sf::sleep(sf::Time(sf::seconds(1)));  // Sleep for 1s
          // delete this->ParticleGenerator.get();       // Delete the random particles generator
          ITEM_HOLDER.getA()->close();          // Deletes the animation window

          exit(EXIT_SUCCESS);
        }
      } else if (Event->type == sf::Event::TextEntered) {
        if (Event->text.unicode < 128) break;
      }
    }

    std::free(Event);
    GameNamespace::VirtualWindowClass::DrawInsideMainWindow(
        ITEM_HOLDER.getA(), ITEM_HOLDER.getB(), ITEM_HOLDER.getC());
  }
}
void GameNamespace::VirtualWindowClass::DrawInsideMainWindow(
    sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD, GameNamespace::VirtualWindowClass* C) {
  WINDOW->clear(sf::Color::Red);
  WINDOW->draw(BackGround->SPRITE);

  // For the particle generator
  ParticleGenerator->Generate();

  ParticleGenerator->InLoopForParticles(WINDOW);
  ParticleGenerator->ClearMemory(WINDOW);

  // Draw the greeting text for the main window
  // WINDOW->draw(GreetingText);
  WINDOW->display();
}
void GameNamespace::VirtualWindowClass::RenderTextures(
    DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) {
  // Inside a separate thread -> Background
  BackGround = std::make_unique<ImageToBeDrawn>();
  BackGround->TEXTURE.loadFromFile("BigSurWallpaper.png");
  BackGround->SPRITE.setTexture(BackGround->TEXTURE);
  BackGround->SPRITE.setScale(0.5, 0.5);
}
#pragma endregion VIRTCLASS_FUNC_IMPLEMENTATIONS
