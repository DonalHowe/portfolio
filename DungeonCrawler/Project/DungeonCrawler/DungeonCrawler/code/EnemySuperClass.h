#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"

class EnemySuperClass
{
public:
	sf::Sprite dumbEnemySprite;
	sf::Texture dumbEnemyTexture;


	sf::Texture walkerEnemyTexture;
	sf::Texture bossTexture;
	sf::Texture m_fireballBossTexture;




	void setUpSprite();
};