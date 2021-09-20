#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Grid.h"
#include "Thor/Vectors.hpp"

// this is the enemy that is used in the breadth first search algorithim
class EnemyBFS
{
	// this it is the farmer states 
	enum class FarmerAnimatedStates
	{
		walking,
		dead,
		attack,
		left,
		right,
		up,
		down
	};
	Grid theGrid;
	sf::Vector2f m_position;
	FarmerAnimatedStates currentFarmerState = FarmerAnimatedStates::down;
	//function to animate the farmer sprites
	void animateSprites();
	//initilises the farmer spites
	void initilise();
	sf::Sprite m_farmerSprite;

	sf::Texture m_farmerTexture;
	// calulate the row and col 
	int calcRow;
	int calcCol;
	// current path x and y of teh player
	float currentPathx;
	float currentPathy;
	//velocity of teh player
	sf::Vector2f currentVelocity;

	sf::Texture m_farmerUpTexture;
	sf::Texture m_farmerDownTexture;
	sf::Texture m_farmerLeftTexture;
	sf::Texture m_farmerRightTexture;
	bool m_isMoving=false;
	bool m_reachedDest=false;
	bool m_foundNextPos=false;
	// current row and current column of teh farmer
	int currentRow;
	int currentCol;


	sf::Vector2f m_farmerPosition;
	// the speed of the farmer
	float m_speed=0.5f;
	// teh accelaeration of the farmer
	sf::Vector2f m_acceleration;
	FarmerAnimatedStates farmerStates;

	int totalElapsed = 0;
	int animationFrame = 0;
	sf::IntRect rectSourceSprite;
	// function to player to find the path to travel
	void getPlayerPath();

public:
	void update(double dt);
	void movement();
	void render(sf::RenderWindow& t_window);
	EnemyBFS();
	sf::Sprite getFarmer();
	sf::Vector2f getPos();

	void animateFarmer(FarmerAnimatedStates t_currentFarmerState);

};

