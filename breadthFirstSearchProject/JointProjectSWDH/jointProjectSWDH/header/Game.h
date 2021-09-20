#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "MainMenu.h"
#include "GameState.h"
#include <iostream>
#include "Player.h"
#include "Cell.h"
#include <map>
#include "enemyChickens.h"
#include "enemybfs.h"
#include  <list>
#include "Grid.h"
#include "CollisionDetector.h"
#include "OrientedBoundingBox.h"
#include "Particle.h"


class Game
{
public:
	
	Game();
	
	void run();
	// other class objects

	MainMenu menuSystem;
	Player myPlayer;
	const static int max_chickens = 6;
	enemyChickens chickenEnemies[max_chickens];
	EnemyBFS farmer;

	Particle particles;
	ParticleSystem particleSystem;
	sf::Font m_font;

	Grid myGrid;

	sf::Vector2f position;

protected:
	sf::Text chickensLeft;
	sf::Text m_winText;
	sf::Text m_gameLostText;
	int chickenDead = 5;
	sf::Vector2f moveFood{ 30000,30000 };
	void update(double dt);
	sf::Sprite m_grassBackgroundSprite;
	sf::Sprite m_sandBackground;
	sf::Texture m_sandTexture;
	sf::Texture m_grassTexture;
	sf::Sprite m_chickenCoup;
	sf::Texture m_coupTexture;
	void render();

	sf::RenderWindow m_window;
	void processEvents();
	 GameState m_gameState{ GameState::Start };

 
	void initilisefileLoads();
	void processGameEvents(sf::Event&);

	void collisionChecker();

};
