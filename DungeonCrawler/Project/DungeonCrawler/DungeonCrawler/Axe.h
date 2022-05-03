#pragma once
#include "Weapons.h"
#include<SFML/Graphics.hpp>
class Axe :public Weapons
{
	sf::Texture m_Texture;
	virtual void weaponType() override;
	virtual void damage() override;
	virtual void animations() override;
	virtual void traits() override;
	std::string m_location;
	float m_FrameIncrement{ 0.05f }; // how fast 
	float m_FrameCounter{ 0.0f };
	int m_Frame{ 0 };
	bool spacePressed = false;

public:
	Axe();
	void setupAxe(std::string t_fileLocation, sf::Vector2f t_size);
	void setPosition(float t_x, float t_y);
	void update(double dt);
	sf::Texture getTexture();
	sf::Sprite GetSprite();
	sf::Sprite m_sprite;
};

