#pragma once
#ifndef ANIMATION_WINDOW_HEADER_H
#define ANIMATION_WINDOW_HEADER_H
#pragma region INCLUDES
#include "StructuresAndOtherFunctions.h"
#include "MainWindowHeader.h"
#include "SpaceShip.h"
#include "RandomParticlesGenerator.h"
#include "EnemySpaceShip.h"
#include "BoomBox.h"

#include <thread>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#pragma endregion INCLUDES

#pragma region ANIMATION_WINDOW
namespace MatthewsNamespace {
	class AnimationWindow {
	private:
		// Same variables
	protected:
		struct ImageToBeDrawn {
			sf::Sprite SPRITE;
			sf::Texture TEXTURE;
		};

		sf::Int32 WWidth;
		sf::Int32 WHeight;
		const std::string WindowTitle;

		std::unique_ptr<ImageToBeDrawn> BackGround;

		sf::Font GlobalWindowFont;
		sf::Text ScoreText, LivesText, GameOverText, PresskeyText, LevelUpText;

		MatthewsNamespace::SpaceShip SpaceShip1, SpaceShip2;
		std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox;

		// Variables related to the main window
		sf::RenderWindow* WindowPointer = NULL;
		sf::Thread* MainWindowThread;
		sf::VideoMode* MainWindowVideo;
		long long Player1Score=0, Player2Score=0;

		MatthewsNamespace::RandomParticlesGenerator* ParticleGenerator;
		std::vector<EnemySpaceShip*> VectorOfEnemies; int enemy_spawn_clock = 0; short Cnt1000 = 0;
		short LevelUpConstant = 0;

	public:
		static int ANIMATION_INSTANCES;
		AnimationWindow(const std::string TITLE, int W, int H) : WindowTitle(TITLE), MainWindowVideo(new sf::VideoMode(W, H)),
			WWidth(static_cast<int>(W)), WHeight(static_cast<int>(H)), ParticleGenerator(new MatthewsNamespace::RandomParticlesGenerator()) {
			// MainWindowThread = new sf::Thread(std::bind(&MainWindowClass::MainWindowThreadExecution,this, *TripleHolder));
			SpaceShip1.setMainWindowSize(WWidth, WHeight);

			MainWindowThread = new sf::Thread([&]() -> void {
				// Create window and set active
				AnimationWindow::WindowPointer = new sf::RenderWindow(*MainWindowVideo, WindowTitle, sf::Style::Titlebar | sf::Style::Close); // Create the window
				WindowPointer->setActive(false);

				std::unique_ptr<TripleItemHolder<sf::RenderWindow, sf::Thread, AnimationWindow>> TripleHolder = std::make_unique<TripleItemHolder
					<sf::RenderWindow, sf::Thread, AnimationWindow>>(WindowPointer, MainWindowThread, this);

				AnimationWindow::MainWindowThreadExecution(*TripleHolder);
				});
			// Create and launch the window thread
			MainWindowThread->launch();
		};

		~AnimationWindow() = default; // Auto deallocate smart pointers 

		void MainWindowThreadExecution(TripleItemHolder<sf::RenderWindow, sf::Thread, AnimationWindow>&ITEM_HOLDER);
		void DrawInsideMainWindow(sf::RenderWindow * WINDOW, sf::Thread * WINTHREAD, AnimationWindow* C);
		void RenderTextures(DoubleItemHolder<sf::RenderWindow, AnimationWindow> ITEM_HOLDER);
	};
}
#pragma endregion ANIMATION_WINDOW

#endif