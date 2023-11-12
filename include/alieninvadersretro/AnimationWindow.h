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
#  include "ImguiRendererForWindow.h"
#  include "MainWindowHeader.h"
#  include "RandomParticlesGenerator.h"
#  include "SpaceShip.h"
#  include "StructuresAndOtherFunctions.h"
#  include "VirtualWindow.h"
#  pragma endregion INCLUDES

#  pragma region ANIMATION_WINDOW
namespace GameNamespace {
  class AnimationWindow : public virtual VirtualWindowClass {
  protected:
    sf::Font GlobalWindowFont;
    sf::Text ScoreText, LivesText, GameOverText, PresskeyText,
        LevelUpText;  // Text displayed in-app

    std::vector<std::unique_ptr<SpaceShip>> SpaceShipPlayersVector;  // Spaceships, a vector of pointers to spaceship objects
    std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox;

    std::vector<std::unique_ptr<EnemySpaceShip>> VectorOfEnemies;
    int enemy_spawn_clock = 0;
    short Cnt1000 = 0;
    short LevelUpConstant = 0;
    long PausedParity = 0;

    // We initialize an imgui renderer
    std::unique_ptr<ImGUIRenderer> ImGuiRenderer;
    inline static AnimationWindow* AnimWin_ = nullptr;

    // Constructor
    AnimationWindow(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H) {
      // Set the space for all the players
      for (const auto& player : SpaceShipPlayersVector) {
        player->setMainWindowSize(
            W, H);  // Sets the windows size as seen from the player's perspective, for all players
                    // that are in the game
      }
    };


  public:
    /**
     * Singletons should not be cloneable.
     */
    AnimationWindow(AnimationWindow& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const AnimationWindow&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static AnimationWindow* GetInstance(const std::string TITLE, int W, int H);
    static void DeleteInstance();
    static bool HasInstance();

    ~AnimationWindow() = default;  // Auto deallocate smart pointers

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              GameNamespace::AnimationWindow* C);
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;

    // Player or memory release related events
    void freeUpMemorySpaceFromPlayerBulletsAfterWindowKill();

    // Boolean value that tells us if there are still user players inside the match
    bool thereAreStillPlayersInsideTheMatch();
    
    // Functions needed for coming back to the main window after the animation window has been killed
    void comeBackToTheMainWindowFromGameWindow(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>&);
  };
}  // namespace GameNamespace
#  pragma endregion ANIMATION_WINDOW

#endif