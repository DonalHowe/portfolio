#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <iostream>
#include "GameState.h"
#include "ScreenSize.h"
#include "chickenFeed.h"

using namespace std;
// cenemy that will use the vision cone
class enemyChickens
{
	// the possible state of the chicken
	enum class VcChickenState {

		patrol,
		attack,
		dead
	};

	//states of the chickens current Animation for which way its facing
	enum class VcChickenAnimState {

		left,
		right,
		up,
		down
	};

	

	

	// the floats


	float xPos;// the x and y position
	float yPos;
	float m_rotationAngle = 2;// rotation angle
	float m_speed;
	//array for the chicken sprites


	sf::Sprite m_chicken;
	sf::Texture chickenTexture; // placeholder texture of the full spritesheet
	
	
	sf::Texture chickenLeftTexture; // 4 actual textures which are a spritesheet for each direction
	sf::Texture chickenRightTexture;
	sf::Texture chickenUpTexture;
	sf::Texture chickenDownTexture;


	sf::Vector2f speed;// speed of the chicken
	
	
	
	int collided = 0;
	int eating = 0;

	bool chickenFed = false;
	bool chickenCollided = false;

	void wallCheck();// checking if the chicken has gone passed the wall of the screen


	//Animation variables and functions 
	int totalElapsed = 0;
	int animationframe = 0;
	sf::IntRect rectSourceSprite;
	void changeStates();

	float m_tempSpeedX = .5;
	float m_tempSpeedY = .5;


	//random starting position of the chickens x and y
	float randXPos = 0;
	float randYPos = 0;

	//random location the chickens will be heading to each specifically x and y
	float randXHeading = 0;
	float randYHeading = 0;

	sf::Vector2f randHeading; //vectors for the start pos and heading for the chickens 
	sf::Vector2f headingVector;

	bool positiveX; //bools for whether the chickens are travelling positively in the X and y directions
	bool positiveY; // true means they are and false meanst theyre not

	bool chickenAlive = true; 
	

public:
	// the max amount of chickens allowed int thge game
	std::vector<sf::Sprite> m_chickenSprites;
	
	// the chicken feed

	chickenFeed theFeed;

	void movement();
	void loadTextures();
	void update(double dt);
	void render(sf::RenderWindow& t_window);


	void animateChicken(VcChickenAnimState t_currentAnimation);
	//function to animate the chicken based on its current animation state

	enemyChickens(); // constructor
	
	VcChickenState chickenState = { VcChickenState::patrol}; // initialise the state of the chicken to patrol

	VcChickenAnimState currentAnimation; //current animtion state of the chicken

	sf::Sprite getBody(); // getter to return the sprite of the chicken

	void killChicken(); // RIP

};

