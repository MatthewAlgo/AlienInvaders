#pragma once
#ifndef ENEMY_SPACE_SHIP_H
#define ENEMY_SPACE_SHIP_H

#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "EnemySpaceShipBullet.h"
#include "RandomParticlesGenerator.h"

#pragma region ENEMY_SPACESHIP_REGION
namespace MatthewsNamespace {
	class EnemySpaceShip {
	protected:
		typedef struct Position {
			double x, y, speed = 0;
		};
		Position POS;

		sf::Texture TextureOfSpaceShip;
		sf::Sprite SpriteOfSpaceShip;
		sf::Vector2f WinSize;

		int shooter_clock = 0;
		short Life = 10;
		// It produces explosions on its bullet collisions -> their data is located here
		sf::Texture Explosion; sf::Sprite ExplosionSprite;

	public:
		// Each spaceship has a queue of bullets
		std::deque<EnemySpaceShipBullet*> BulletDeque;
		static int LIFE_SUPPLIER;

		inline void MoveUp() { if (POS.y - 5 > 0 && POS.y - 5 < WinSize.y) POS.y -= 5; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveDown() { if (POS.y + 5 > 0 && POS.y + 5 < WinSize.y) POS.y += 5; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveLeft() { if (POS.x - 5 > 0 && POS.x - 5 < WinSize.y) POS.x -= 5; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveRight() { if (POS.x + 5 > 0 && POS.x + 5 < WinSize.y) POS.x += 5; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }

		EnemySpaceShip(sf::Vector2f WindowSize, sf::Texture Texture, int WWidth) : WinSize(WindowSize), TextureOfSpaceShip(Texture) {
			// POS.y = WindowSize.y / 2;
			POS.x = 0;
			// Set the position of the spaceship
			SpriteOfSpaceShip.setTexture(TextureOfSpaceShip);
			this->setSpaceShipPosition(MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(0, WWidth), 0);
			
			// Init the explosion if this constructor is called
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		EnemySpaceShip(sf::Vector2f WindowSize) : WinSize(WindowSize) { // Init the explosion if this constructor is called
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		EnemySpaceShip() { // Init the explosion if this constructor is called
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		~EnemySpaceShip() = default;

		void setTexture(sf::Texture& texture) { TextureOfSpaceShip = texture; SpriteOfSpaceShip.setTexture(TextureOfSpaceShip); }
		void setTexture(std::string FileName) { TextureOfSpaceShip.loadFromFile(FileName); SpriteOfSpaceShip.setTexture(TextureOfSpaceShip); }
		
		void setSprite(sf::Sprite & sprite) { SpriteOfSpaceShip = sprite; }
		void centerInWindow(sf::Vector2f WindowSize) { POS.y = WindowSize.y / 2; POS.x = WindowSize.x / 2; }
		void setSpaceShipPosition(double X, double Y) { POS.x = X; POS.y = Y; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		void scaleSpaceShip(int scx, int scy) { SpriteOfSpaceShip.setScale(scx, scy); }

		sf::Texture* getSpaceShipTexture() { return &TextureOfSpaceShip; }
		sf::Sprite* getSpaceShipSprite() { return &SpriteOfSpaceShip; }
		sf::Vector2f getSpaceShipPosition() { return sf::Vector2f(POS.x, POS.y); }
		short* getLife() { return &Life; }
		void setLife(short L) { Life = L; }

		void setMainWindowSize(int X, int Y) { WinSize.x = X; WinSize.y = Y; }
		void Shoot();

		void GenerateInDrawFunctionOfMainWindow(sf::RenderWindow* Window, std::string SpaceShipTextureName);

		void DrawBulletsInWindow(sf::RenderWindow* Window, int XSSPos, int YSSPos, short& SS);

		void FreeUpMemoryFromBullets(sf::RenderWindow* Window);

		void Draw_IterateExistingItem(sf::RenderWindow* Window);
		void MoveRandomLeftOrRightorUpOrDown();
		void Die(); // Free up the buffer of bullets

	};

}
#pragma endregion ENEMY_SPACESHIP_REGION

#endif
