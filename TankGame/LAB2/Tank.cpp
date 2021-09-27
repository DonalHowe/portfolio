#include "Tank.h"



void Tank::increaseSpeed()
{
	m_previousSpeed = m_speed;

		if (m_speed < 200.0)
		{
			m_speed += 2;
		}
	
	
}

void Tank::decreaseSpeed()
{
	m_previousSpeed = m_speed;

		if (m_speed > -150.0)
		{
			m_speed -= 1.5;
		}
	
	
}

void Tank::increseRotaion()
{
	m_previousRotation = m_rotation;
	m_rotation += 1;

	
		
		if (m_rotation == 360.0)
		{
			m_rotation = 0;
		}
	
	
}

void Tank::decreaseRotation()
{
	m_previousRotation = m_rotation;
	m_rotation -= 1;

		
		if (m_rotation == 0.0)
		{
			m_rotation = 359.0;
		}
	

}

void Tank::turretRotaion()
{
	m_previousTurretRotation = m_Turretrotation;
	m_Turretrotation -= 1;


	if (m_Turretrotation == 0.0)
	{
		m_Turretrotation = 359.0;
	}
}

void Tank::turrertRotaionAnti()
{
	m_previousTurretRotation = m_Turretrotation;
	m_Turretrotation += 1;


	if (m_Turretrotation == 0.0)
	{
		m_Turretrotation = 359.0;
	}
}

void Tank::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
		m_bulletDirection = { 0,-5 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
		m_bulletDirection = { 0,5 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increseRotaion();
		m_bulletDirection = { 5,0};
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
		m_bulletDirection = { -5,0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		
		turrertRotaionAnti();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		turretRotaion();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		centreTurret( m_rotation);
	}

}

void Tank::deflect()
{
	// In case tank was rotating.
	adjustRotation();
	
	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_previousPosition = m_tankBase.getPosition();
		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) || CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
}

Tank::Tank(sf::Texture const & texture, std::vector<sf::Sprite>& m_wallSprites)
: m_texture(texture)
, m_wallSprites(m_wallSprites)
, tankBullet(m_wallSprites,texture)
{
	initSprites();
}

void Tank::update(double dt,sf::Vector2f &t_pos, int& t_rotation)
{	
	handleKeyInput();
	offScreen();
		sf::Vector2f newTankPosition;

		rotRadiand = (MathUtility::DEG_TO_RAD * m_rotation);

		newTankPosition.x = t_pos.x + std::cosf(rotRadiand) * m_speed * (dt / 1000);

		newTankPosition.y = t_pos.y + std::sinf(rotRadiand) * m_speed * (dt / 1000);


		t_pos = newTankPosition;
		t_rotation = m_Turretrotation;
		m_tankBase.setPosition(t_pos);
		m_tankBase.setRotation(m_rotation);
	
		m_turret.setPosition(t_pos);
		m_turret.setRotation(t_rotation + m_rotation);
		
		m_speed = std::clamp(m_speed,-50.0,150.0);
		m_speed *= .95;
	
		if (checkWallCollision())
		{
			deflect();
		}
	
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::setPosition(sf::Vector2f t_pos)
{
	//t_pos = m_position;
	m_tankBase.setPosition(t_pos);
	m_turret.setPosition(t_pos);
}

bool Tank::offScreen()
{
	if (m_tankBase.getPosition().x<0 || m_tankBase.getPosition().x >ScreenSize::s_width)
	{
		return true;
	}
	else if(m_tankBase.getPosition().y<0 || m_tankBase.getPosition().y >ScreenSize::s_height)
	{
		return true;
	}
	else {
		return false;
	}
}

void Tank::centreTurret(double t_rotation)
{
	

		/*
		m_turret.setRotation(t_rotation);
		hasBeenCentred = true;*/
		if (m_Turretrotation < m_rotation)
		{
			// abs is absolute value
			// in C++, use std::abs()
			if (abs(m_Turretrotation - m_rotation) < 180)
			{
				// Call your increaseTurretRotation() function to increment the turret angle
				turrertRotaionAnti();
			}
			else
			{
				
				turretRotaion();
			}
		}
		else
		{
			if (abs(m_Turretrotation - m_rotation) < 180)
			{
				
				turrertRotaionAnti();
			}

		}


	

}
void Tank::adjustRotation()
{
	// If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_Turretrotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_Turretrotation = m_previousTurretRotation;
	}
}

sf::Vector2f Tank::getPosition() const
{
	return m_tankBase.getPosition();
}



void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);

	
	m_rectangleBase.setPosition(2, 43);
	m_rectangleBase.setSize(sf::Vector2f{ 79,43 });
	
	
}

