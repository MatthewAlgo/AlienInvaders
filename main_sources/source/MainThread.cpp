#include <iostream>

#include "alieninvadersretro/AnimationWindow.h"
#include "alieninvadersretro/BoomBox.h"
#include "alieninvadersretro/MainWindowHeader.h"
#include "alieninvadersretro/PlayerStatsAndScoresWindow.h"
#include "alieninvadersretro/Player.h"

#ifdef __linux__
#  include <X11/Xlib.h>
#endif

namespace GameNamespace {
  class MainWindowClass;
}

// C++17 Application -> Used the filesystem header from standard library
int main() {
  // Linux compile: g++ -g -std=c++17 -v AnimationWindowSource.cpp BoomBoxSource.cpp
  // EnemySpaceShipSource.cpp MainThread.cpp MainWindowSource.cpp SpaceShipSource.cpp
  // -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lX11 -o AlienInvadersRetro.elf

#ifdef __linux__
  XInitThreads(); // Calls the Thread Initialization for Linux
#endif

  GameNamespace::MainWindowClass* MyMainWindow = new GameNamespace::MainWindowClass(
      "AlienInvasion - Main Menu", 1000, 500);

  // Start a thread with a qt5 player selector window
  GameNamespace::INIT_PLAYER_STATS_AND_SCORES_WINDOW();
  // Start a thread with a qt5 player selector window
  GameNamespace::AnimationWindow::INIT_ANIMATION_WINDOW();

  
  // Eventually start a window that is capable of adding players to the match
  GameNamespace::BoomBox::INIT_BOOMBOX_MAIN();

  std::cin.get();
  return 0;
}
