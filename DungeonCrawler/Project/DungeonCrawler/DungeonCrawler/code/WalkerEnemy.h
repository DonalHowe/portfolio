#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "EnemySuperClass.h"
#include "GameStates.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include"include/Thor/Time.hpp"
#include "ScreenSize.h"

class WalkerEnemy : public EnemySuperClass
{
private:
	GolemDirection directionState = GolemDirection::Stop;
	

	int const NUMBER_OF_GOLEMS = 5;
	float randomSpeed;
	float minRandomSpeed = 0.001f;
	float maxRandomSpeed = 0.8f;
	float timer;
	float m_FrameIncrement{ 0.05f }; // how fast 
	float m_FrameCounter{ 0.0f };
	int m_Frame{ 0 };

	int stop, right, left, down, up;

	
	bool directionSelected = false;
	bool animationIsOn = true;
	
	sf::Vector2f startPos{ 530.0f,400.0f };
	sf::Vector2f currentPos;
	float m_speed = 1.0f;
	float m_previousSpeed = 0.0f;
	float m_golemSpeed ;
	bool rockMoving = false;
	void setUpSprite();
	void randomDirSelect();
	void animate();
	void movement();


public:
	sf::Sprite tempSprite;
	sf::Sprite bloodStainSprite;
	sf::Sprite rockSprite[20];
	bool getRockMoving();
	sf::Texture bloodTexture;
	sf::Texture rockTexture;

	WalkerEnemy();
	sf::Sprite GetSprite() const;
	int GetMaxGolems() const;
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	void deflect();
};