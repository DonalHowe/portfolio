#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
class mazeGuide
{
public:
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	mazeGuide();
	~mazeGuide();
	void movement(sf::Vector2f pos);
	sf::CircleShape m_shape;

private:
	void setupGuideSprite();

	
};

