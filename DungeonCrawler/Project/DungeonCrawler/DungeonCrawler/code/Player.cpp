#include "Player.h"




sf::RectangleShape Player::GetDashStamina()
{
	return dashStamina;
}



void Player::Walkingmovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//m_playerSprite.setScale(-1, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && dashAmount > 1.0f)
		{
			dashAmount = dashAmount - 70.0f;

			m_speed = dashSpeed;

		}
		m_previousSpeed = m_speed;

		currentPos = m_playerSprite.getPosition();
		currentPos.x -= m_speed;

		m_playerFrameCounter += m_playerFrameIncrement;
		m_playerFrame = static_cast<int>(m_playerFrameCounter) % 4; // change valuues later to see the difference 
		//m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 31, 74, 29 , 40 });
		//m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 30, 0, 32 , 40 });
		m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 96, 100, 96, 96 });

		m_playerSprite.setPosition(currentPos);
	
		m_direction = 2;
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && dashAmount > 1.0f)
		 {
			 dashAmount = dashAmount - 70.0f;
			 m_speed = dashSpeed;

		 }
		 m_previousSpeed = m_speed;

		 currentPos = m_playerSprite.getPosition();
		 currentPos.x += m_speed;

		 m_playerFrameCounter += m_playerFrameIncrement;
		 m_playerFrame = static_cast<int>(m_playerFrameCounter) % 4; // change valuues later to see the difference 
		// m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 31,202, 31 , 40 });
		 m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 96,199, 96 , 90 });

		 m_playerSprite.setPosition(currentPos);
		 m_direction = 1;

	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		 m_previousSpeed = m_speed;

		 currentPos = m_playerSprite.getPosition();
		 currentPos.y -= m_speed;

		 m_playerFrameCounter += m_playerFrameIncrement;
		 m_playerFrame = static_cast<int>(m_playerFrameCounter) % 4; // change valuues later to see the difference 
		 //m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 64, 20, 64 , 40 });
		 m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 96, 288, 96 , 90 });

		 m_playerSprite.setPosition(currentPos);
		 m_direction = 3;

	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		 m_previousSpeed = m_speed;

		 currentPos = m_playerSprite.getPosition();
		 currentPos.y += m_speed;

		 m_playerFrameCounter += m_playerFrameIncrement;
		 m_playerFrame = static_cast<int>(m_playerFrameCounter) % 4; // change valuues later to see the difference 
		// m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 64,131, 64 , 40 });
		 m_playerSprite.setTextureRect(sf::IntRect{ m_playerFrame * 96, 3, 96 , 90 });
		 m_direction = 4;
		 m_playerSprite.setPosition(currentPos);
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	 {
		 m_speed = 2.0f;
	 }
	 else
	 {
		 m_speed = 1.0f;
	 }
	

}

int Player::GetPlayerDirection()
{
	return 	m_direction;
	
}


Sword* Player::GetSword()
{
	return m_Sword;
}

Axe* Player::GetAxe()
{
	return m_axe;
}

bool Player::collisionWithGolem(sf::Sprite& t_collisionSprite)
{

	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		return true;
	}
	return false;
}

Player::~Player()
{

	delete m_Sword;
	delete m_axe;
	

	
}

bool Player::collisionWithSword(sf::Sprite& t_collisionSprite)
{
	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		return true;
	}
	return false;
}

bool Player::collisionWithAxe(sf::Sprite& t_collisionSprite)
{
	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		return true;
	}
	return false;
}

Player::Player()
{
	createPlayer();
}

sf::Sprite Player::GetSprite()
{
	return m_playerSprite;
}

sf::Vector2f Player::GetStartPos()
{
	return startPos;
}

void Player::SetSpritePos(sf::Vector2f t_newPosition)
{
	m_playerSprite.setPosition(t_newPosition);
}



void Player::createPlayer()
{
	if (!m_playerTexture.loadFromFile("rescources/images/USED-IMAGES/playerSprite2.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	if (!m_fireballTexture.loadFromFile("rescources/images/USED-IMAGES/fireball.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(startPos);
	m_playerSprite.setTextureRect(sf::IntRect{  96, 3, 96 , 90 });
	m_playerSprite.setOrigin(m_playerSprite.getGlobalBounds().width/2, m_playerSprite.getGlobalBounds().height/2);
	//m_playerSprite.setScale(1.59, 1.59);

	
	dashStamina.setPosition(100,100);
	dashStamina.setFillColor(sf::Color::Transparent);
	dashStamina.setSize(sf::Vector2f(dashAmount,20.0f ));
	

	playerHealthBar.setPosition(100, 100);
	playerHealthBar.setFillColor(sf::Color::Green);
	playerHealthBar.setSize(sf::Vector2f(playerHp, 12.0f));



	fireBall.setTexture(m_fireballTexture);
	fireBall.setPosition(200,-9900);
	fireBall.setOrigin(69, 55);
	fireBall.setScale(0.7f, 0.7f);


	if (playerHp <= 50.0f)
	{
		playerHealthBar.setFillColor(sf::Color::Yellow);
	}
	else if(playerHp <=25.0f)
	{
		playerHealthBar.setFillColor(sf::Color::Red);
	}

	if (!m_fireballSoundsBuffer.loadFromFile("rescources/sound/fireball.ogg"))
	{
		std::cout << "cant load song file" << std::endl;
	}
	m_fireballSounds.setBuffer(m_fireballSoundsBuffer);

}


void Player::animateFireball()
{
	m_fireBallFrameCounter += m_fireBallFrameIncrement;
	m_fireBallFrame = static_cast<int>(m_fireBallFrameCounter) % 6; // change valuues later to see the difference 
	fireBall.setTextureRect(sf::IntRect{ m_fireBallFrame * 133, 3, 133 , 110 });
}


void Player::update(double dt)
{
	if (dashAmount < 100)
	{
		dashAmount = dashAmount + .5f;
	}
	playerHealthBar.setSize(sf::Vector2f(playerHp, 12.0f));
	//playerHp = playerHp - 0.5;
	playerHealthBar.setPosition(m_playerSprite.getPosition().x - 50, m_playerSprite.getPosition().y - 60);
	Walkingmovement();
	dashStamina.setSize(sf::Vector2f(dashAmount, 20.0f));

	visionCone();

	if (playerHp <= 50.0f)
	{
		playerHealthBar.setFillColor(sf::Color::Yellow);
	}
	if (playerHp <= 25.0f)
	{
		playerHealthBar.setFillColor(sf::Color::Red);
	}
	if (playerHp <= 0.0f)
	{
		playerHp = 0.0f;
	}


	animateFireball();
	
}

void Player::render(sf::RenderWindow& t_window)
{

	t_window.draw(m_playerSprite);
	t_window.draw(dashStamina);
	t_window.draw(playerHealthBar);
	t_window.draw(fireBall);

	 mousePosition = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));


}

bool Player::collisionWithKey(sf::Sprite & t_collisionSprite)
{
	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		return true;
	}
	return false;
}

bool Player::collisionWithEnemy(sf::Sprite& t_collisionSprite)
{
	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		

		return true;
	}
	return false;
}

void Player::visionCone()
{
	coneOfVision = sf::VertexArray( sf::Triangles,3 );
	//VCpointOne= VCpointOne+{vcLength*m_angle}
	//calculations for the points to be to the left and to the right
}

void Player::shootFireBall()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireBall.getPosition().y < 0)
	{
		fireBall.setPosition(m_playerSprite.getPosition());

		float angleShot = atan2(mousePosition.y - fireBall.getPosition().y, mousePosition.x - fireBall.getPosition().x);

		angleShot2 = angleShot;  //so it goes in a straight line
		shot = true;
		m_fireballSounds.play();
	}

	if (shot)
	{
		fireBall.move(cos(angleShot2) * 2.0f, 0);
		fireBall.move(0, sin(angleShot2) * 2.0f);
	}
}

void Player::setcanAttackEnemy(bool t_canUSeAxe,bool t_canUSeSword)
{
	canUseSword = t_canUSeSword;
	canUseAxe = t_canUSeAxe;
}


bool Player::collisionWithDoor(sf::Sprite& t_collisionSprite) // used later when door is a sprite
{
	if (CollisionDetector::collisions(m_playerSprite, t_collisionSprite))
	{
		std::cout << "COLLIDED SHIP WITH door" << std::endl;

		return true;
	}
	return false;
}

bool Player::checkWallCollision(sf::Sprite& t_wallCollision) // will finish later
{
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	sf::Sprite const& sprite = t_wallCollision;
	
	// Checks if either the ship base or turret has collided with the current wall sprite.
	if (CollisionDetector::collisions(m_playerSprite, sprite) ||
		CollisionDetector::collisions(m_playerSprite, sprite))
	{
		std::cout << "COLLIDED SHIP WITH cage" << std::endl;

		return true;
	}
	
	else
	{
		return false;
	}

}

void Player::deflect()
{
	if (m_speed != 0)
	{
		// Back up to position in previous frame.
		m_playerSprite.setPosition(currentPos);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 1.9f;
		}
		else
		{
			m_speed = -1.9f;
		}
	}
}


void Player::screenBoundForLevelThree(int t_width, int t_height)
{
	float minPosX = t_width - t_width + 1;
	float maxPosX = t_width - 1;

	float minPosY = t_height - t_height + 1;
	float maxPosY = t_height - 1;
	//std::cout << "PLAYER X:"<< m_playerSprite.getPosition().x << std::endl;

	if (m_playerSprite.getPosition().x > maxPosX)
	{ 
		m_playerSprite.setPosition(minPosX+88, m_playerSprite.getPosition().y);
	}

	//BOTTOM
	if (m_playerSprite.getPosition().y > maxPosY -50)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, maxPosY-50);
	}

	//LEFT
	if (m_playerSprite.getPosition().x < minPosY +88)
	{
		m_playerSprite.setPosition(maxPosX, m_playerSprite.getPosition().y);
	}

	//TOP
	if (m_playerSprite.getPosition().y < 500)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, 500);
	}


	if (fireBall.getPosition().y > m_playerSprite.getPosition().y)
	{
		fireBall.setPosition(0, -9999);
	}

	if (fireBall.getPosition().x > maxPosX)
	{
		fireBall.setPosition(0, -9999);
	}

	if (fireBall.getPosition().x < minPosX)
	{
		fireBall.setPosition(0, -9999);
	}



	

}
