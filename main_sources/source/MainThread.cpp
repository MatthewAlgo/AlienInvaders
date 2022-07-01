#include <iostream>

#include "alieninvadersretro/AnimationWindow.h"
#include "alieninvadersretro/BoomBox.h"
#include "alieninvadersretro/MainWindowHeader.h"
#include "alieninvadersretro/PlayerStatsAndScoresWindow.h"

#ifdef __linux__
#  include <X11/Xlib.h>
#endif

// TODO: add pause button inside the game
// TODO: add high score mechanics
// TODO: implement design pattern: singleton

// C++17 Application -> Used the filesystem header from standard library
int main() {
  // Linux compile: g++ -g -std=c++17 -v AnimationWindowSource.cpp BoomBoxSource.cpp
  // EnemySpaceShipSource.cpp MainThread.cpp MainWindowSource.cpp SpaceShipSource.cpp
  // -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lX11 -o AlienInvadersRetro.elf

#ifdef __linux__
  // XInitThreads(); // Calls the Thread Initialization for Linux
#endif

  /// BETA area
  ///	MatthewsNamespace::PlayerStats* Window = new MatthewsNamespace::PlayerStats("Test", 1000,
  ///500);
  ///

  MatthewsNamespace::MainWindowClass* MyMainWindow;
  MyMainWindow = new MatthewsNamespace::MainWindowClass("AlienInvasion - Main Menu", 1000, 500);
  MatthewsNamespace::BoomBox::INIT_BOOMBOX_MAIN();

  std::cin.get();
  return 0;
}
