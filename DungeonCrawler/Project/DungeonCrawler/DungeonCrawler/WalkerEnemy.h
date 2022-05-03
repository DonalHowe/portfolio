#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "EnemySuperClass.h"



class WalkerEnemy : public EnemySuperClass
{
	float enemyMaxX = 800;
	float enemyMinX = 510;

	float enemyMaxY = 600;
	float enemyMinY = 400;

public:
	WalkerEnemy();

	void setUpSprite();
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	void animate();
	void movement();
	bool goDown = false;
	bool animControl = false;

	sf::Vector2f startPos{ 530.0f,400.0f };
	sf::Vector2f currentPos;
	sf::Vector2f speedGuard{ 1.0f,0.0f };

	float m_FrameIncrement{ 0.05f }; // how fast 
	float m_FrameCounter{ 0.0f };
	int m_Frame{ 0 };
};
{

};

