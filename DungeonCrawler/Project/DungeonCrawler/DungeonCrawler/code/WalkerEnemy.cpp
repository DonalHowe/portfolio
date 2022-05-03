#include "WalkerEnemy.h"


bool WalkerEnemy::getRockMoving()
{
	return rockMoving;
}

WalkerEnemy::WalkerEnemy()
{
	setUpSprite();
	srand(static_cast <unsigned> (time(0)));

}

sf::Sprite WalkerEnemy::GetSprite() const
{
	return tempSprite;
}

int WalkerEnemy::GetMaxGolems() const
{
	return NUMBER_OF_GOLEMS;
}

void WalkerEnemy::setUpSprite()
{
	if (!walkerEnemyTexture.loadFromFile("rescources/images/USED-IMAGES/golem-walk.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	if (!bloodTexture.loadFromFile("rescources/images/USED-IMAGES/bloodStain.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	if (!rockTexture.loadFromFile("rescources/images/USED-IMAGES/rock.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	bloodStainSprite.setTexture(bloodTexture);
	bloodStainSprite.setPosition(2000,2000);
	bloodStainSprite.setScale(0.1, 0.1);

	for (int i = 0; i < 19; i++)
	{
		rockSprite[i].setTexture(rockTexture);
		rockSprite[i].setPosition(2000, 2000);
		rockSprite[i].setScale(0.1, 0.1);
	}
	//rockSprite.setScale(0.1, 0.1);


	
	tempSprite.setTexture(walkerEnemyTexture);
	currentPos = startPos;
	tempSprite.setPosition(rand() % ScreenSize::screen_width + 90, rand() % ScreenSize::screen_height + 90);
	tempSprite.setScale(2, 2);

	
}


void WalkerEnemy::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < NUMBER_OF_GOLEMS; i++)
	{
		t_window.draw(tempSprite);
	}

	t_window.draw(bloodStainSprite);
	for (int i = 0; i < 19; i++)
	{
		t_window.draw(rockSprite[i]);
	}

}

void WalkerEnemy::update(double dt)
{
	animate();
	movement();
	
	
	// the random direction of the golem
	
	if (directionSelected==false)
	{
		
		timer ++ ;
		if (timer == 99)
		{
			randomDirSelect();
			directionSelected = false;
			
		}
	}
	if (timer > 100&& timer / dt<600 &&directionSelected == false)
	{
		
		
		if (timer ==599)
		{
			randomDirSelect();
			directionSelected = false;
		}
		timer++;
	}
	if (timer > 1100 && timer / dt < 1600&& directionSelected == false)
	{
		
		
		if (timer == 1599)
		{
			randomDirSelect();
			directionSelected = false;
		}
		timer++;
	}
	if (timer> 2100 && timer / dt < 2600== directionSelected == false)
	{
	
		if (timer == 2499)
		{
			randomDirSelect();
			directionSelected = false;
		}
		
		timer++;
	}
	if (timer > 3100 && timer / dt < 3600&& directionSelected == false)
	{
	
		
		if (timer == 3599)
		{
			randomDirSelect();
			directionSelected = false;
		}
		timer++;
	}
	if (timer > 3600 && directionSelected == false)
	{
		timer = 0;
	}

	
}

void WalkerEnemy::animate()
{
	m_FrameIncrement = 0.05f; // how fast 

	if (animationIsOn)
	{
		if (directionState == GolemDirection::Up)
		{
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
			tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 0, 64 , 64 });
			for (int i = 0; i < 1; i++)
			{
				rockSprite[i].setPosition(tempSprite.getPosition().x + 20, tempSprite.getPosition().y + 50);
			}

		}

		else if (directionState == GolemDirection::Left)
		{
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
			tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 64, 64 , 64 });
			for (int i = 0; i < 1; i++)
			{
				rockSprite[i].setPosition(tempSprite.getPosition().x +20, tempSprite.getPosition().y+50);

			}

		}

		else if (directionState == GolemDirection::Down)
		{
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
			tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 128, 64 , 64 });
			for (int i = 0; i < 1; i++)
			{
				rockSprite[i].setPosition(tempSprite.getPosition().x + 20, tempSprite.getPosition().y + 50);

			}

		}

		else if (directionState == GolemDirection::Right)
		{
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
			tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 192, 64 , 64 });
			for (int i = 0; i < 1; i++)
			{
				rockSprite[i].setPosition(tempSprite.getPosition().x + 20, tempSprite.getPosition().y + 50);

			}

		}
		else
		{
			m_FrameIncrement = 0.01f; // how fast 
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
			tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 128, 64 , 64 });
			for (int i = 0; i < 1; i++)
			{
				rockSprite[i].setPosition( tempSprite.getPosition());
			}

		}
	}

	if (!animationIsOn)
	{
		m_FrameIncrement = 0.01f; // how fast 
		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 7; // change valuues later to see the difference 
		tempSprite.setTextureRect(sf::IntRect{ m_Frame * 64, 128, 64 , 64 });
	}


}

void WalkerEnemy::movement()
{
	randomSpeed = minRandomSpeed + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRandomSpeed - minRandomSpeed)));

	if (directionState == GolemDirection::Right)
	{	
		m_speed = 1;
		m_golemSpeed = 5;
		for (int i = 0; i < 19; i++)
		{
			rockSprite[i].move(-m_golemSpeed, 0);
			rockMoving = true;
		}
		currentPos = tempSprite.getPosition();
		tempSprite.move(m_speed, 0);			
		m_previousSpeed = m_speed;
		animationIsOn = true;
	}
	if (directionState == GolemDirection::Down)
	{
		m_speed = 1;
		m_golemSpeed = 5;
		for (int i = 0; i < 19; i++)
		{
			rockSprite[i].move( 0, -m_golemSpeed);
			rockMoving = true;
		}
		currentPos = tempSprite.getPosition();
		tempSprite.move(0, m_speed);		
		m_previousSpeed = m_speed;
		animationIsOn = true;

	}
	if (directionState == GolemDirection::Left)
	{
		m_speed = 1;
		currentPos = tempSprite.getPosition();
		m_golemSpeed = 5;
		for (int i = 0; i < 19; i++)
		{
			rockSprite[i].move(m_golemSpeed,0);
		}
		rockMoving = true;
		tempSprite.move(-m_speed, 0);	
		m_previousSpeed = m_speed;
		animationIsOn = true;

	}
	if (directionState == GolemDirection::Up)
	{
		m_speed = 1;
		currentPos = tempSprite.getPosition();
		m_golemSpeed = 5;
		for (int i = 0; i < 19; i++)
		{
			rockSprite[i].move(0, m_golemSpeed);
			rockMoving = true;
		}
		tempSprite.move(0, -m_speed);	
		m_previousSpeed = m_speed;
		animationIsOn = true;

	}
	if (directionState == GolemDirection::Stop)
	{
		currentPos = tempSprite.getPosition();
	    tempSprite.move(0, 0);   
		rockMoving = false;
		m_previousSpeed = m_speed;
		animationIsOn = true;

	}

}


void WalkerEnemy::randomDirSelect()
{
	directionState = GolemDirection(rand() % 5);
	std::cout << "direction selected is :" << static_cast<int>(directionState) << std::endl;
	directionSelected = true;
}



void WalkerEnemy::deflect()
{
	if (m_speed != 0)
	{
		// Back up to position in previous frame.
		tempSprite.setPosition(currentPos);
		animationIsOn = false;
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 0;
		}
		else
		{
			m_speed = 0;
		}
	}
}




