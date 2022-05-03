#include "Axe.h"

void Axe::weaponType()
{
}

void Axe::damage()
{
}

void Axe::animations()
{
}

void Axe::traits()
{
}

Axe::Axe()
{
}

void Axe::setupAxe(std::string t_fileLocation,  sf::Vector2f t_size)
{
	m_location = t_fileLocation;
	if (!m_Texture.loadFromFile(t_fileLocation))
	{
		std::cout << "cant load sprite" << std::endl;

	}
	m_sprite.setTexture(m_Texture);
	m_sprite.setScale(t_size);
	m_sprite.setTextureRect(sf::IntRect{ 20, 0, 500 , 420 });
}

void Axe::setPosition(float t_x, float t_y)
{
}

void Axe::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed)
	{
		for (int i = 0; i < 5; i++)
		{
			m_FrameCounter += m_FrameIncrement;
			m_Frame = static_cast<int>(m_FrameCounter) % 5; // change valuues later to see the difference 
			m_sprite.setTextureRect(sf::IntRect{ m_Frame * 500, 0, 500 , 420 });
			i++;
		}
	}
	else
	{
		m_sprite.setTextureRect(sf::IntRect{ 20, 0, 500 , 420 });
	}


}

sf::Texture Axe::getTexture()
{
    return m_Texture;
}

sf::Sprite Axe::GetSprite()
{
    return m_sprite;
}
