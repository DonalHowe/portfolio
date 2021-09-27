#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "CollisionDetector.h"
#include "LevelLoader.h"
#include "ScreenSize.h"
/// <summary>
/// author: donal howe
/// </summary>
class Enemies
{
	// the radius for the player
	const  int RADIUS= 15;
	// function to offset the enemies if they have spawned on the walls
	void offsetEnemies();
	// function to create the enemy 
	void createEnemy();
	
	std::vector<sf::Sprite>& m_wallSprites;
	bool checkWallCollision();
	

	sf::Vector2f m_startPosition;
	sf::Vector2f enemyOffset{60,60};
	void enemyDeSpawn(sf::Clock t_colourClock);
	sf::Vector2f enemyTwoPos;
	sf::Vector2f enemyThreePos;
	sf::Vector2f enemyOnePos;
	sf::Vector2f enemyFourPos;
	float duration;
	
public:
	bool firstenemyDestroyed=false;
	// to set the duration which the enemies stay on teh screen
	void setDuration(float& t_durationOne, float& durTwo, float& durThree, float& durFour);
	bool enemiesKilled = false;// bool to check if the enemies have been killed
	void update(double dt, sf::Clock t_clock,sf::Vector2f &t_enemyPosOne, sf::Vector2f& t_enemyPosTwo, sf::Vector2f& t_enemyPosThree, sf::Vector2f& t_enemyPosFour);
	// render fuinction
	void render(sf::RenderWindow &t_window);
	// enemy constructor
	Enemies(std::vector<sf::Sprite>& t_wallSprite);
	// the colour clock to show when the enemies are about to despawn
	sf::Clock colourClock;
	// the maximum amount of enemies allowed in the game
	const static int MAX_ENEMIES = 4;
	// the variable to have the enemies spawn one after the other in sequence
	int delayedSpawn=0;
	// enemies array
	std::vector < sf::Sprite> m_enemiesArray;
	sf::Texture m_enemyTexture;
	sf::Sprite enemySprite;
};
//
