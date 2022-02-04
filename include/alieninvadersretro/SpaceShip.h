#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SpaceShipBullet.h"
#include "EnemySpaceShip.h"

#pragma region SPACESHIP_CLASS
namespace MatthewsNamespace {
	class SpaceShip {
	protected:
		typedef struct Position {
			double x, y;
		};
		Position POS;

		sf::Texture TextureOfSpaceShip;
		sf::Sprite SpriteOfSpaceShip;
		sf::Vector2f WinSize;

		// It produces explosions on its bullet collisions -> their data is located here
		sf::Texture Explosion; sf::Sprite ExplosionSprite;

	public:
		short Life = 50;
		// Each spaceship has a queue of bullets
		std::deque<SpaceShipBullet*> BulletDeque;

		inline void MoveUp() { if(POS.y - 20 > 0 && POS.y-20 < WinSize.y) POS.y -= 30; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveDown() { if (POS.y + 20 > 0 && POS.y + 20 < WinSize.y) POS.y += 30; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveLeft() { if (POS.x - 20 > -60 && POS.x - 20 < WinSize.x) POS.x -= 30; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		inline void MoveRight() { if (POS.x + 20 > -60 && POS.x + 20 < WinSize.x) POS.x += 30; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }

		SpaceShip(sf::Vector2f WindowSize, sf::Texture Texture) : WinSize(WindowSize), TextureOfSpaceShip(Texture) {
			// Init the explosion if this constructor is called
			POS.y = WindowSize.y / 2;
			POS.x = WindowSize.x / 2;
			// Set the position of the spaceship
			SpriteOfSpaceShip.setTexture(TextureOfSpaceShip);
			SpriteOfSpaceShip.setPosition(sf::Vector2f(POS.x, POS.y));

			// Init the explosion
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		SpaceShip(sf::Vector2f WindowSize) : WinSize(WindowSize) {
			// Init the explosion if this constructor is called
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		SpaceShip() {
			// Init the explosion if this constructor is called
			Explosion.loadFromFile("Explosion.png");
			ExplosionSprite.setTexture(Explosion);
			ExplosionSprite.setScale(0.1, 0.1);
		}
		~SpaceShip() = default;

		void setTexture(sf::Texture& texture) { TextureOfSpaceShip = texture; }
		void setSprite(sf::Sprite& sprite) { SpriteOfSpaceShip = sprite; }
		void centerInWindow(sf::Vector2f WindowSize) { POS.y = WindowSize.y / 2; POS.x = WindowSize.x / 2; }
		void setSpaceShipPosition(double X, double Y) { POS.x = X; POS.y = Y; SpriteOfSpaceShip.setPosition(POS.x, POS.y); }
		void scaleSpaceShip(int scx, int scy) { SpriteOfSpaceShip.setScale(scx, scy); }

		sf::Texture* getSpaceShipTexture()  { return &TextureOfSpaceShip; }
		sf::Sprite* getSpaceShipSprite()  { return &SpriteOfSpaceShip; }
		sf::Vector2f getSpaceShipPosition() { return sf::Vector2f(POS.x, POS.y); }
		short* getLife() { return &Life; }
		void setLife(short L) { Life = L; }

		void setMainWindowSize(int X, int Y) { WinSize.x = X; WinSize.y = Y; }

		void Shoot(int PlayerScore);
		int IterateThroughBullets(sf::RenderWindow* WINDOW, std::vector<EnemySpaceShip*>& Enemies);
		void FreeUpMemoryBullets();

	};
}
#pragma endregion SPACESHIP_CLASS
#endif