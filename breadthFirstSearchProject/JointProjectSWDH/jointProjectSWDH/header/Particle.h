#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


class Particle
{
public:
	int timetoLive;
	sf::Vector2f velocity;
	sf::RectangleShape shape;

	void draw(sf::RenderWindow& win)
	{
		if (timetoLive > 0)
		{
			win.draw(shape);
		}
	}
	void update()
	{
		if (timetoLive > 0)
		{
			shape.move(velocity);

			timetoLive--;
		}
	}

	Particle() {}

	Particle(sf::Vector2f pos, sf::Vector2f vel)
	{
		shape.setSize(sf::Vector2f(6, 6));
		shape.setPosition(pos);
		shape.setFillColor(sf::Color::Red);

		velocity = vel;
		timetoLive = 200;
		timetoLive = rand() % 150;

	}
};


#define maxParticles 50
class ParticleSystem
{
public:

	Particle particles[maxParticles];
	sf::Vector2f position;
	void Initialise(sf::Vector2f pos)
	{
		position = pos;
		for (int i = 0; i < maxParticles; i++)
		{
			particles[i] = Particle(position, sf::Vector2f(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2));
		}
	}
	void update()
	{
		for (int i = 0; i < maxParticles; i++)
		{

			particles[i].update();


		}
	}
	void Draw(sf::RenderWindow& win)
	{
		for (int i = 0; i < maxParticles; i++)
		{
			particles[i].draw(win);
		}
	}

	ParticleSystem() {}
};