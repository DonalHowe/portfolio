#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Player
{
private:
	
	
	sf::Sprite playerSprite; // sprite of the player

	sf::Texture playerTexture; // initiial texture of the whole spritesheet

	sf::Texture playerLeftTexture; // 4 spritesheets for each direction
	sf::Texture playerRightTexture;
	sf::Texture playerUpTexture;
	sf::Texture playerDownTexture;

	void loadFiles(); // function to load all the files
	float m_playerSpeed = 1.5;

	float totalElapsed = 0; //animation based variables
	int animationframe = 0;
	sf::IntRect rectSourceSprite;


public:
	float getPlayerSpeed();
	void setPlayerSpeed(float t_playerSpeed);
	PlayerAnimations animationState{ PlayerAnimations::idle };
	Player();
	sf::Vector2f playerPos;
	void initialise();
	void update(double dt);
	void draw(sf::RenderWindow& t_window);
	void movePlayer();
	void animatePlayer(PlayerAnimations t_playerAnimState);
	

	sf::Sprite getBody();

};

