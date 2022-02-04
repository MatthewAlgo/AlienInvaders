#pragma once
#ifndef MAIN_WINDOW_HEADER_H
#define MAIN_WINDOW_HEADER_H

#pragma region INCLUDES
#include "StructuresAndOtherFunctions.h"
#include "RandomParticlesGenerator.h"

#include <iostream>
#include <thread>
#include <functional>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#pragma endregion INCLUDES

#define U_P std::unique_ptr

#pragma region CLASS_REGION
namespace MatthewsNamespace {
	class MainWindowClass {
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
		sf::Text GreetingText, TextBTN1, TextBTN2;
		ImageToBeDrawn MenuBox1, MenuBox2, MenuBox3;
		std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox;

		// Variables related to the main window
		sf::RenderWindow* WindowPointer = NULL;
		sf::Thread* MainWindowThread;
		sf::VideoMode* MainWindowVideo;
		// std::thread* STDMainWindowThread;
		MatthewsNamespace::RandomParticlesGenerator* ParticleGenerator;
		
		// Variables related to the textures and design elements
	public:

		MainWindowClass(const std::string TITLE, int W, int H) : WindowTitle(TITLE), MainWindowVideo(new sf::VideoMode(W, H)), 
				WWidth(static_cast<int>(W)), WHeight(static_cast<int>(H)), ParticleGenerator(new MatthewsNamespace::RandomParticlesGenerator()) {
			// MainWindowThread = new sf::Thread(std::bind(&MainWindowClass::MainWindowThreadExecution,this, *TripleHolder));
			MainWindowThread = new sf::Thread([&]() -> void {
					// Create window and set active
					MainWindowClass::WindowPointer = new sf::RenderWindow(*MainWindowVideo, WindowTitle, sf::Style::Titlebar | sf::Style::Close); // Create the window
					WindowPointer->setActive(false);

					std::unique_ptr<TripleItemHolder<sf::RenderWindow, sf::Thread, MainWindowClass>> TripleHolder = std::make_unique<TripleItemHolder
						<sf::RenderWindow, sf::Thread, MainWindowClass>>(WindowPointer, MainWindowThread, this);
					
					MainWindowClass::MainWindowThreadExecution(*TripleHolder);
				});
			// Create and launch the window thread
			MainWindowThread->launch();
		};
		~MainWindowClass() = default; // Auto deallocate smart pointers 

		void MainWindowThreadExecution(TripleItemHolder<sf::RenderWindow, sf::Thread, MainWindowClass>& ITEM_HOLDER);
		void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD, MainWindowClass* C);
		void RenderTextures(DoubleItemHolder<sf::RenderWindow, MainWindowClass> ITEM_HOLDER);
		
	};
};

#pragma endregion CLASS_REGION

#endif