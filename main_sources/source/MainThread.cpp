#include <iostream>

#include "alieninvadersretro/AnimationWindow.h"
#include "alieninvadersretro/BoomBox.h"
#include "alieninvadersretro/MainWindowHeader.h"
#include "alieninvadersretro/PlayerStatsAndScoresWindow.h"

#ifdef __linux__
#  include <X11/Xlib.h>
#endif

// TODO: Solve Linux issue: alieninvadersretro: /home/matthewalgo/VSCode/AlienInvadersTest/main_libraries/imgui/imgui.cpp:3843: ImGuiIO& ImGui::GetIO(): Assertion `GImGui != __null && "No current context. Did you call ImGui::CreateContext() and ImGui::SetCurrentContext() ?"' failed.
// fish: Job 1, './alieninvadersretro q' terminated by signal SIGABRT (Abort) + Other windows freeze when animation window is closed 

// Late TODO: Implement design pattern: singleton
// Late TODO: Add a networking library and start working on a multiplayer network component 

// C++17 Application -> Used the filesystem header from standard library
int main() {
  // Linux compile: g++ -g -std=c++17 -v AnimationWindowSource.cpp BoomBoxSource.cpp
  // EnemySpaceShipSource.cpp MainThread.cpp MainWindowSource.cpp SpaceShipSource.cpp
  // -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lX11 -o AlienInvadersRetro.elf

#ifdef __linux__
  XInitThreads(); // Calls the Thread Initialization for Linux
#endif

  /// BETA area
  /// Nothing Here for now :)

  MatthewsNamespace::MainWindowClass* MyMainWindow;
  MyMainWindow = new MatthewsNamespace::MainWindowClass("AlienInvasion - Main Menu", 1000, 500);
  MatthewsNamespace::BoomBox::INIT_BOOMBOX_MAIN();

  std::cin.get();
  return 0;
}
