#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

// this is the class that makes the chicken feed
class chickenFeed
{
	// the chicken feed sprite
	sf::Sprite m_feedSprite;
	// number of chickens which in turn makes the same amount of feed
	int chickens;
	// teh position of the feed
	sf::Vector2f m_position;
	// the texture for the feed
	sf::Texture m_feedTexture;
public:
	// getter and setter functions
	sf::Sprite getSprite();

	void setPosition(sf::Vector2f t_position);


	void render(sf::RenderWindow& t_window);
	// overloaded and default constructor
	chickenFeed(const static int t_chickens) :chickens(t_chickens) {
		
	};
	chickenFeed() {
		if (!m_feedTexture.loadFromFile("./resources/img/chickenFeed.png"))
		{
			std::cout << "no load " << std::endl;
		}
		m_feedSprite.setTexture(m_feedTexture);
		m_feedSprite.setScale(.15, .15);
		m_feedSprite.setPosition(m_position);
	};

};

