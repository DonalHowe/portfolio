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


class Boss : public EnemySuperClass
{
private:
	float m_FrameIncrement{ 0.05f }; // how fast 
	float m_FrameCounter{ 0.0f };
	int m_Frame{ 0 };

	float m_fireBallFrameIncrement{ 0.05f }; // how fast 
	float m_fireBallFrameCounter{ 0.0f };
	int m_fireBallFrame{ 0 };
	void setUpSprite();
	void animate();
	void animateFireball();
	float moveSpeed = 1.5f;
	sf::RectangleShape bossHealthBar;

public:
	sf::Sprite bossSprite;
	float m_bossHP = 400.0f;
	Boss();
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	void movement(int t_width, int t_height);
	void wipeBallMovement(sf::Vector2f pos);

	sf::Sprite fireBallBossSprite;
	sf::Texture wipeBallBossTexture;

	sf::Sprite wipeBallBossSprite;
	sf::Sprite towerSprite[2];
	sf::Texture towerTexture;
	sf::Texture deadbossTexture;
	sf::Sprite deadbossSprite;
	int checkBoss = 1;


};