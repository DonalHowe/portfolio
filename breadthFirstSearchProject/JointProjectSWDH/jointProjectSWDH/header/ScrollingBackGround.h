#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
/// <summary>
/// the animaterd background which is used in teh main menu
/// </summary>
class ScrollingBackGround
{
	// sf::rectshape setup variables
	const static int maxBoxes = 10;
	sf::RectangleShape backGroundArray[maxBoxes];
	sf::Vector2f startPos{ 1200,800 };
	sf::Vector2f boxPos{ startPos };
public:
	// constructor and necessary functions
	ScrollingBackGround();
	void initilise();
	void update(double dt);
	void render(sf::RenderWindow &t_window);
};

