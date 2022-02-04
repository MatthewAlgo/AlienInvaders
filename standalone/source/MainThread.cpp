#include "alieninvadersretro/MainWindowHeader.h"
#include "alieninvadersretro/AnimationWindow.h"
#include "alieninvadersretro/BoomBox.h"

#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

// C++17 Application -> Used the filesystem header from standard library
int main()
{
    // Linux compile: g++ -g -std=c++17 -v AnimationWindowSource.cpp BoomBoxSource.cpp EnemySpaceShipSource.cpp MainThread.cpp MainWindowSource.cpp SpaceShipSource.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lX11 -o AlienInvadersRetro.elf 

#ifdef __linux__
	XInitThreads();
#endif

	MatthewsNamespace::MainWindowClass* MyMainWindow;
	MyMainWindow = new MatthewsNamespace::MainWindowClass("AlienInvasion - Main Menu", 1000, 500);
	MatthewsNamespace::BoomBox::INIT_BOOMBOX_MAIN();

	std::cin.get();
	return 0;
}
