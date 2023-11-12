#pragma once
#ifndef PLAYER_STATS_WINDOW_H
#  define PLAYER_STATS_WINDOW_H

#  pragma region INCLUDES
#  include <SFML/Audio.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>
#  include <cstring>
#  include <filesystem>
#  include <functional>
#  include <optional>
#  include <string>
#  include <thread>

#  include "MainWindowHeader.h"
#  include "StructuresAndOtherFunctions.h"
#  pragma endregion INCLUDES

namespace fs = std::filesystem;

#  pragma region ANIMATION_WINDOW
namespace GameNamespace {
  class BoomBox : public virtual GameNamespace::VirtualWindowClass {
  private:
    // Nothing here for now
  protected:
    // Including variables that are inherited
    sf::Font GlobalWindowFont;  // For the font
    sf::Text GreetingText, SoundToggleText, MusicToggleText;
    std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox, Speaker1;
    ImageToBeDrawn Speaker2, SoundBox, MusicBox;

  public:
    static int BOOMBOX_INSTANCES;
    struct DJ {
      sf::Sound CollisionSound, ShootSound, PShootSound, DeathSound, WelcomeSound, WindowSound,
          MainThemeSound, WrongSelectionSound, UpgradeSound, EvilSound, SOUND_MAIN;
      sf::SoundBuffer CollisionSoundBuffer, ShootSoundBuffer, PShootSoundBuffer, DeathSoundBuffer,
          WelcomeSoundBuffer, WindowSoundBuffer, MainThemeSoundBuffer, WrongSelectionSoundBuffer,
          UpgradeSoundBuffer, EvilSoundBuffer, SOUND_MAIN_BUFFER;
    };

    // Static variables -> The boombox can be accessed from anywhere
    static std::unique_ptr<DJ> LocalDJ;
    static bool IS_SOUND_ENABLED, IS_MUSIC_ENABLED;
    static std::vector<std::string> WavFilesFromDirectory;

    BoomBox(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H){};

    ~BoomBox() = default;  // Auto deallocate smart pointers

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              VirtualWindowClass* C) override;
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;

    // Static functions -> The boombox can be accessed from anywhere
    static void LoadAudioInMemory();
    static void ShootSoundEffect();
    static void PShootSoundEffect();
    static void WindowSoundEffect();
    static void WindowCollisionEffect();
    static void WrongSelectionEffect();
    static void GameOverEffect();
    static void WelcomeEffect();
    static void UpgradeEffect();
    static void EvilEffect();

    static void StartMainThemeSong();
    static sf::Sound* getMainTheme();

    // For the AnimationWindow BoomBox
    static void LoadFileNameVector();
    static void INIT_BOOMBOX_MAIN();
    static std::optional<std::string> RandomSongGenerator();
    // Render WAV sine wave inside the BoomBox
    void RenderLinesInCurrentFrame(sf::RenderWindow* BoomBoxWindow, int precision);
  };
}  // namespace GameNamespace
#  pragma endregion ANIMATION_WINDOW

#endif
