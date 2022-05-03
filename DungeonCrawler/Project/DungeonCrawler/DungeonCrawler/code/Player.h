#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Weapons.h"
#include "Sword.h"
#include "Axe.h"
#include "MathUtility.h"
#include <SFML/Audio.hpp>

class Player
{
	Weapons* m_weapons;
	Sword* m_Sword = new Sword;
	Axe* m_axe = new Axe;
	
	sf::Texture m_playerTexture;
	sf::Texture m_fireballTexture;

	sf::Vector2f m_velocity;
	sf::Vector2f currentPos;
	float m_speed = 1.0f;
	sf::Vector2f movement;
	float dashAmount = 150.0f;
	float dashSpeed = 15.0f;
	int m_direction = 0; // DIRECTION 1 = RIGHT and LEFT = 2 and UP is 3
	float m_playerFrameIncrement{ 0.05f }; // how fast 
	float m_playerFrameCounter{ 0.0f };
	int m_playerFrame{ 0 };

	float m_fireBallFrameIncrement{ 0.05f }; // how fast 
	float m_fireBallFrameCounter{ 0.0f };
	int m_fireBallFrame{ 0 };

	float 	m_previousSpeed;
	bool canUseSword = false;
	bool canUseAxe = false;
	bool shot = false;
	sf::RectangleShape playerHealthBar;
	sf::RectangleShape dashStamina;
	sf::VertexArray coneOfVision;

	sf::Vector2f VCpointOne;
	sf::Vector2f VCpointTwo;
	sf::Vector2f VCpointThree;

	constexpr static float vcLength = 300.0f;
	float m_angle;
	
	void createPlayer();
	sf::Vector2f startPos{ 200, 250 };
	sf::Vector2f mousePosition;
	float angleShot2 = 0.0f;
	sf::SoundBuffer m_fireballSoundsBuffer;
	sf::Sound m_fireballSounds;

public:
	Player();
	sf::Sprite m_playerSprite;
	sf::Sprite fireBall;

	float playerHp = 100.0f;

	sf::Sprite GetSprite();
	void SetSpritePos(sf::Vector2f t_newPosition);
	int GetPlayerDirection();
	void visionCone();
	void shootFireBall();
	Sword* GetSword();
	Axe* GetAxe();
	sf::RectangleShape GetDashStamina();
	
	sf::Vector2f GetStartPos();
	void update(double dt);
	void render(sf::RenderWindow& t_window);
	bool collisionWithKey(sf::Sprite& t_collisionSprite);
	
	void setcanAttackEnemy(bool t_canUSeAxe,bool t_canUseSword);
	void animateFireball();
	bool collisionWithDoor(sf::Sprite& t_collisionSprite);
	
	bool checkWallCollision(sf::Sprite& t_wallCollision);
	bool collisionWithEnemy(sf::Sprite& t_collisionSprite);
	void deflect();
	void Walkingmovement();
	void screenBoundForLevelThree(int t_width, int t_height);

	bool collisionWithSword(sf::Sprite& t_collisionSprite);
	bool collisionWithAxe(sf::Sprite& t_collisionSprite);

	bool collisionWithGolem(sf::Sprite& t_collisionSprite);

	~Player();

};

