#pragma once
#ifndef VIRTUAL_WINDOW_HEADER_H
#  define VIRTUAL_WINDOW_HEADER_H
#  pragma region INCLUDES
#  include <SFML/Audio.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>
#  include <functional>
#  include <thread>

#  include "RandomParticlesGenerator.h"
#  include "StructuresAndOtherFunctions.h"
#  pragma endregion INCLUDES

#  pragma region VIRTUAL_WINDOW
namespace MatthewsNamespace {
  class VirtualWindowClass {
  protected:
    struct ImageToBeDrawn {
      sf::Sprite SPRITE;
      sf::Texture TEXTURE;
    };

    sf::Int32 WWidth;
    sf::Int32 WHeight;
    const std::string WindowTitle;

    // Variables related to the main window
    std::unique_ptr<ImageToBeDrawn> BackGround;
    std::unique_ptr<sf::RenderWindow> WindowPointer;
    std::unique_ptr<sf::Thread> MainWindowThread;
    std::unique_ptr<sf::VideoMode> MainWindowVideo;

    std::unique_ptr<MatthewsNamespace::RandomParticlesGenerator> ParticleGenerator;

  public:
    VirtualWindowClass(const std::string TITLE, int W, int H)
        : WindowTitle(TITLE),
          MainWindowVideo(new sf::VideoMode(W, H)),
          WWidth(static_cast<int>(W)),
          WHeight(static_cast<int>(H)),
          ParticleGenerator(new MatthewsNamespace::RandomParticlesGenerator()) {
      // MainWindowThread = new
      // sf::Thread(std::bind(&MainWindowClass::MainWindowThreadExecution,this, *TripleHolder));

      MainWindowThread = std::make_unique<sf::Thread>([&]() -> void {
        // Create window and set active
        VirtualWindowClass::WindowPointer
            = std::make_unique<sf::RenderWindow>(*MainWindowVideo, WindowTitle,
                                   sf::Style::Titlebar | sf::Style::Close);  // Create the window
        WindowPointer->setActive(false);

        std::unique_ptr<TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>>
            TripleHolder
            = std::make_unique<TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>>(
                WindowPointer.get(), MainWindowThread.get(), this);

        this->MainWindowThreadExecution(*TripleHolder);
      });
      // Create and launch the window thread
      MainWindowThread->launch();
    };

    virtual ~VirtualWindowClass() = default;  // Auto deallocate smart pointers

    virtual void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER);
    virtual void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                                      VirtualWindowClass* C);
    virtual void RenderTextures(DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER);
  };
}  // namespace MatthewsNamespace
#  pragma endregion VIRTUAL_WINDOW

#endif