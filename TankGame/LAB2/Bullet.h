#pragma once
#include "SFML/Graphics.hpp"
#include "MathUtility.h"
#include "Thor/Vectors.hpp"
#include "CollisionDetector.h"
#include <iostream>
#include "SFML/Audio.hpp"

/// <summary>
/// author: donal howe
/// </summary>
class Bullet
{// private bullet member variables
	const int PROJECTILE_SPEED = 800;
	int bulletTimer = 0;// the bullet buffer 
	bool bulletReady = false;
	sf::Vector2f startPoint;
	std::vector<sf::Sprite> & m_wallSprites;// the wallsprites so the bullet collides with the wall
	sf::Texture const& m_texture;// the bullet texture thats passed from the game to tank to the bullet
	double bulletRotation;// the bullets rotation
	sf::SoundBuffer m_soundBuffer;// the sound for when the bullet shoots
	sf::Sound m_tankSound;
	void setupAudio();// function to setup the audio
public:
	bool checkWallCollision();// returns whether the bullet collides with the wall
	sf::Texture m_bulletTexture;
	sf::Sprite bulletSprite;
	Bullet(std::vector<sf::Sprite> &t_wallSprite, sf::Texture const& texture);
	bool bulletFired = false;
	bool readyTofire = false;
	void update(double dt, sf::Vector2f& t_pos,int &t_tankRotation, double&t_tankBase);
	void render(sf::RenderWindow& t_window);
	void createSprite();
	
	

};

