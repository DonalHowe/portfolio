#include "Bullet.h"



void Bullet::createSprite()// function to create the bullet
{
		bulletSprite.setTexture(m_texture);
		sf::IntRect bulletRect(8, 177, 6, 9);
		bulletSprite.setTextureRect(bulletRect);
		bulletSprite.setOrigin(bulletRect.width / 2, bulletRect.height / 2);
		bulletSprite.setPosition(300, 300);
		bulletSprite.setScale(2.5, 2.5);
}


Bullet::Bullet(std::vector<sf::Sprite>& t_wallSprite, sf::Texture const& texture) : m_wallSprites(t_wallSprite), m_texture(texture)
{
	//m_wallSprites = t_wallSprite;
	createSprite();
	setupAudio();
}



void Bullet::update(double dt, sf::Vector2f& t_pos, int &t_tankRotation, double &t_tankBase)// function whiuch handles the bullet movement and rotation
{

    // If space has been pressed (fire request)
	bulletTimer++;
	std::cout << bulletTimer << std::endl;     
	bulletRotation = t_tankBase + t_tankRotation;
	if (readyTofire == true&&bulletTimer>150 )
	{
		m_tankSound.play();
		bulletSprite.setPosition(t_pos);
		bulletSprite.setRotation(t_tankBase + t_tankRotation);
		//bulletSprite.setRotation(t_tankRotation);

		startPoint = sf::Vector2f(
			t_pos.x + 1 * std::cos(bulletRotation * MathUtility::DEG_TO_RAD),
			t_pos.y + 1 * std::sin(bulletRotation * MathUtility::DEG_TO_RAD)
		);
		

		startPoint = thor::unitVector(startPoint - t_pos);

		bulletTimer = 0;
		readyTofire = false;
		bulletFired = true;
		bulletReady == false;
		
	}
	bulletSprite.move(startPoint.x * PROJECTILE_SPEED * (dt / 1000), startPoint.y * PROJECTILE_SPEED * (dt / 1000));
	

	checkWallCollision();
	
	if (checkWallCollision() == true)
	{
		bulletSprite.setPosition(2000,2000);
		
	}
    
}
void Bullet::setupAudio()//setsup the bullet audio
{
	if (!m_soundBuffer.loadFromFile("./resources/images/bulletSound.wav"))
	{
		std::cout << "error loading sound" << std::endl;
	}
	m_tankSound.setBuffer(m_soundBuffer);
}
bool Bullet::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(bulletSprite, sprite))
		{
			return true;
		}
	}
	return false;
}

void Bullet::render(sf::RenderWindow& t_window)
{
	if (bulletFired == true)
	{
		t_window.draw(bulletSprite);
    }

}



