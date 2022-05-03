#include "DumbEnemy.h"


DumbEnemy::DumbEnemy()
{
	setUpSprite();
}



void DumbEnemy::setUpSprite()
{
	if (!dumbEnemyTexture.loadFromFile("rescources/images/USED-IMAGES/dumbEnemy.png"))
	{

		std::cout << "cant load sprite" << std::endl;

	}
	dumbEnemySprite.setTexture(dumbEnemyTexture);
	dumbEnemySprite.setPosition(startPos);
	dumbEnemySprite.setScale(1, 1);
	currentPos = startPos;
}



void DumbEnemy::update(double dt)
{
	movement();
	if (!goDown && !animControl){animate();}

}

void DumbEnemy::animate()
{
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 3; // change valuues later to see the difference 
		dumbEnemySprite.setTextureRect(sf::IntRect{ m_Frame * 48, 64, 48 , 64 });
}

void DumbEnemy::movement()
{

	if (dumbEnemySprite.getPosition().x > enemyMaxX) // go down
	{
		goDown = true;
		animControl = true;
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 3; // change valuues later to see the difference 
		dumbEnemySprite.setTextureRect(sf::IntRect{ m_Frame * 48, 140, 48 , 64 });

		speedGuard.y = 1.0f;
		speedGuard.x = 0.0f;
	}

	if (dumbEnemySprite.getPosition().y > enemyMaxY) // go left 
	{
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 3; // change valuues later to see the difference 
		dumbEnemySprite.setTextureRect(sf::IntRect{ m_Frame * 48, 192, 48 , 64 });

		speedGuard.y = 0.0f;
		speedGuard.x = -1.0f;
	}

	if (dumbEnemySprite.getPosition().x < enemyMinX) // go up
	{
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 3; // change valuues later to see the difference 
		dumbEnemySprite.setTextureRect(sf::IntRect{ m_Frame * 48, 0, 48 , 64 });

		goDown = false;
		speedGuard.y = -1.0f;
		speedGuard.x = 0.0f;
	}
	if (dumbEnemySprite.getPosition().y < enemyMinY && goDown == false) // go right
	{
		// animation
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 3; // change valuues later to see the difference 
		dumbEnemySprite.setTextureRect(sf::IntRect{ m_Frame * 48, 64, 48 , 64 });

		speedGuard.y = 0.0f;
		speedGuard.x = 1.0f;
	}

	currentPos.x = currentPos.x + speedGuard.x;
	currentPos.y = currentPos.y + speedGuard.y;

	dumbEnemySprite.setPosition(currentPos.x, currentPos.y);


}

void DumbEnemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(dumbEnemySprite);

}