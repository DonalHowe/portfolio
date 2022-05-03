#pragma once
#include "Weapons.h"
class Sword :public Weapons
{
	
	sf::Texture m_swordTexture;
	virtual void weaponType() override;
	virtual void damage() override;
	virtual void animations() override;
	virtual void traits() override;
	std::string m_location;

public:
	Sword();
	void setupSword(std::string t_fileLocation);

	void update(double dt);
	sf::Texture getTexture();
	sf::Sprite GetSprite();
	sf::Sprite m_sprite;
};

