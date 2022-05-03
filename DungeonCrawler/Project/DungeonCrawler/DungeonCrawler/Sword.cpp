#include "Sword.h"

void Sword::weaponType()
{
	std::cout << " this is an sword" << std::endl;
}

void Sword::damage()
{
	std::cout << " 3" << std::endl;
}

void Sword::animations()
{
	std::cout << " sword animations" << std::endl;
}

void Sword::traits()
{
	std::cout << "sword traits" << std::endl;
}

void Sword::setupSword(std::string t_fileLocation)
{
	m_location = t_fileLocation;
	if (!m_swordTexture.loadFromFile(t_fileLocation))
	{
		std::cout << "cant load sprite" << std::endl;

	}
	m_sprite.setTexture(m_swordTexture);

	m_sprite.setScale(0.5, 0.5);
}


void Sword::update(double dt)
{
	
}

Sword::Sword()
{
	
}

sf::Texture Sword::getTexture()
{
	return m_swordTexture;
}

sf::Sprite Sword::GetSprite()
{
	return m_sprite;
}
