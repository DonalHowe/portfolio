#include "Enemies.h"

void Enemies::createEnemy()// creates the targets
{
	srand(time(nullptr));
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!m_enemyTexture.loadFromFile("./resources/images/Zebra.png"))
		{
			std::string s("Error loading texture");
			throw std::exception(s.c_str());
		}
		enemySprite.setTexture(m_enemyTexture);
		enemySprite.setScale(.5,.5);
		m_startPosition.x = rand() % ScreenSize::s_width/2 +1;
		m_startPosition.y = rand() % ScreenSize::s_height/2+ 1;
		enemySprite.setPosition(m_startPosition);
		m_enemiesArray.push_back(enemySprite);
		
		
	}
	
}






void Enemies::offsetEnemies()// if the enemies spawn on the walls they will be repositioned
{
	if (checkWallCollision() == true)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			m_enemiesArray.at(i).setPosition(m_startPosition + enemyOffset);
		}
	}
	
}

void Enemies::enemyDeSpawn(sf::Clock t_colourClock)// handles the changing of colour to show the player that the enemies are about to despawn
{
	if (t_colourClock.getElapsedTime().asSeconds() >= 5&& t_colourClock.getElapsedTime().asSeconds() <= 9)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Blue));

		}
	}

	if (t_colourClock.getElapsedTime().asSeconds() >= 10 && t_colourClock.getElapsedTime().asSeconds() <= 14)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Magenta));
			if (t_colourClock.getElapsedTime().asSeconds() >= 15)
			{
				m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Red));

			}
			if (t_colourClock.getElapsedTime().asSeconds() >= 14)
			{
				m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Red));

			}
			if (t_colourClock.getElapsedTime().asSeconds() >= 16)
			{
				m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Red));

			}
			if (t_colourClock.getElapsedTime().asSeconds() >= 13)
			{
				m_enemiesArray.at(i).setColor(sf::Color(sf::Color::Red));

			}
		}
	}
}

void Enemies::setDuration(float& t_durationOne, float& durTwo, float& durThree, float& durFour)
{
}
// handles all of the target spawning and updating
void Enemies::update(double dt, sf::Clock t_clock, sf::Vector2f& t_enemyPosOne, sf::Vector2f& t_enemyPosTwo, sf::Vector2f& t_enemyPosThree, sf::Vector2f& t_enemyPosFour)
{
	colourClock = t_clock;
	
	checkWallCollision();
	offsetEnemies();
	if (checkWallCollision() == true)
	{
		offsetEnemies();
	}
	
	enemyFourPos = t_enemyPosFour;
	enemyTwoPos = t_enemyPosTwo;
	enemyOnePos = t_enemyPosOne;
	enemyThreePos = t_enemyPosThree;
	
	if (firstenemyDestroyed == false)
	{
		m_enemiesArray.at(0).setPosition(enemyOnePos);
		m_enemiesArray.at(1).setPosition(enemyTwoPos);
		m_enemiesArray.at(2).setPosition(enemyThreePos);
		m_enemiesArray.at(3).setPosition(enemyFourPos);

	}
	

		


	enemyDeSpawn(colourClock);
	
}

void Enemies::render(sf::RenderWindow & t_window)// the render fucntion which displays the targets one after the other
{
	
	if (colourClock.getElapsedTime().asSeconds() >= 5)
	{
		t_window.draw(m_enemiesArray.at(0));
    }
	if (colourClock.getElapsedTime().asSeconds() >= 8)
	{
		t_window.draw(m_enemiesArray.at(1));
	}

	if (colourClock.getElapsedTime().asSeconds() >= 11)
	{
		t_window.draw(m_enemiesArray.at(2));
	}

	if (colourClock.getElapsedTime().asSeconds() >= 14)
	{
		t_window.draw(m_enemiesArray.at(3));
	}

		
}

Enemies::Enemies(std::vector<sf::Sprite>& t_wallSprite): m_wallSprites(t_wallSprite)
{
	createEnemy();
}

bool Enemies::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (CollisionDetector::collision(m_enemiesArray.at(i), sprite))
			{
				return true;
			}
		}
		
	}
	return false;
}