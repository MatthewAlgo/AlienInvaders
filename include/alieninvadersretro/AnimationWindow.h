#pragma once
#ifndef ANIMATION_WINDOW_HEADER_H
#  define ANIMATION_WINDOW_HEADER_H
#  pragma region INCLUDES
#  include <SFML/Audio.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>
#  include <functional>
#  include <thread>

#  include "BoomBox.h"
#  include "EnemySpaceShip.h"
#  include "RandomParticlesGenerator.h"
#  include "SpaceShip.h"
#  include "StructuresAndOtherFunctions.h"
#  include "VirtualWindow.h"
#  include "ImguiRendererForWindow.h"
#  pragma endregion INCLUDES

#  pragma region ANIMATION_WINDOW
namespace MatthewsNamespace {
  class AnimationWindow : public virtual VirtualWindowClass {
  private:
    // AnimationWindow(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H){};
    // // Private constructor AnimationWindow(Singleton& other) = delete;
    // AnimationWindow& operator=(AnimationWindow& other) = delete;

  protected:
    sf::Font GlobalWindowFont;
    sf::Text ScoreText, LivesText, GameOverText, PresskeyText,
        LevelUpText;  // Text displayed in-app

    MatthewsNamespace::SpaceShip SpaceShipMainPlayer;  // Spaceships
    std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox;
    long long Player1Score = 0;  // Player Score

    std::vector<EnemySpaceShip*> VectorOfEnemies;
    int enemy_spawn_clock = 0;
    short Cnt1000 = 0;
    short LevelUpConstant = 0;

    // We initialize an imgui renderer
    std::unique_ptr<ImGUIRenderer> ImGuiRenderer; 

  public:
    static int ANIMATION_INSTANCES;

    AnimationWindow(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H) {
      SpaceShipMainPlayer.setMainWindowSize(
          W, H);  // Sets the windows size as seen from the player's perspective

      // We init the IMGUI Context;
      ImGuiRenderer = std::make_unique<ImGUIRenderer>(this->WindowPointer);
    };
    static AnimationWindow* const AnimWin;  // Singleton instance

    ~AnimationWindow() = default;  // Auto deallocate smart pointers

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              VirtualWindowClass* C) override;
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;
  };
}  // namespace MatthewsNamespace
#  pragma endregion ANIMATION_WINDOW

#endif