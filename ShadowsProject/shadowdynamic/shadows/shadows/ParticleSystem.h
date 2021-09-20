#pragma once
//auhtors dawid jerdonek, donal howe, filip rusiecki
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00249662_itcarlow_ie/EUZs41WtdvRDrd4ZRac_oPwBXg_v7CkU2RP-Jdka_JZDFw?e=xe9K6J

#include <SFML/Graphics.hpp>
#define maxParticles 50
class Particle
{
public:
	int timeActive;
	sf::Vector2f particleVelocity;
	sf::RectangleShape particleShape;

	void Render(sf::RenderWindow& win)
	{
		if (timeActive > 0)
		{
			win.draw(particleShape);
		}
	}
	void Update()
	{
		if (timeActive > 0)
		{
			particleShape.move(particleVelocity);

			timeActive--;
		}
	}

	Particle() {}

	Particle(sf::Vector2f pos, sf::Vector2f vel)
	{
		particleShape.setSize(sf::Vector2f(6, 6));
		particleShape.setPosition(pos);
		particleShape.setFillColor(sf::Color::Blue);

		particleVelocity = vel;
		//timetoLive = 200;
		timeActive = rand() % 150;

	}
};



class ParticleSystem
{
public:
	
	Particle theParticles[maxParticles];
	sf::Vector2f particlePos;
	void Initialise(sf::Vector2f pos)
	{
		particlePos=pos;
		for (int i =0;i<maxParticles;i++)
		{
			theParticles[i] = Particle(particlePos,sf::Vector2f(rand() / double(RAND_MAX)*4-2,rand() / double(RAND_MAX)*4-2));
		}
	}
	void Update()
	{
		for (int i =0;i<maxParticles;i++)
		{
			
			theParticles[i].Update();
			
		
		}
	}
	void Draw(sf::RenderWindow &win )
	{
		for (int i =0;i<maxParticles;i++)
		{
			theParticles[i].Render(win);
		}
	}

	ParticleSystem(){}
};

