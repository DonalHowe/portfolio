#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Key
{
	sf::Texture m_Texture;
	float m_FrameIncrement{ 0.05f }; // how fast 
	float m_FrameCounter{ 0.0f };
	int m_Frame{ 0 };
	
public:
	sf::Sprite m_Sprite;

	
	Key();
	void setupSprite(sf::Texture& t_texture,sf::Vector2f t_position,sf::Vector2f t_scale);
	void render(sf::RenderWindow& t_window);
	void update(double dt);

};

