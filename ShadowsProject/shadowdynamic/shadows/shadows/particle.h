#pragma once
#include "SFML/Graphics.hpp"
//auhtors dawid jerdonek, donal howe, filip rusiecki
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00249662_itcarlow_ie/EUZs41WtdvRDrd4ZRac_oPwBXg_v7CkU2RP-Jdka_JZDFw?e=xe9K6J
class Particle
{
public:
	int timeToLive = 50;
	sf::RectangleShape particleShape;
	sf::Vector2f particleVelocity;
	void render(sf::RenderWindow& t_window)
	{
		t_window.draw(particleShape);
	}
	void update()
	{
		if (timeToLive > 0) {
			particleShape.move(particleVelocity);
			timeToLive--;
		}
	}
	Particle() {

	}
	Particle(sf::Vector2f t_pos,sf::Vector2f t_velocity)
	{
		particleShape.setSize(sf::Vector2f(8, 8));
		particleShape.setFillColor(sf::Color::Blue);
		particleShape.setPosition(t_pos);
		particleVelocity = t_velocity;
		timeToLive = 200;
	}
};

