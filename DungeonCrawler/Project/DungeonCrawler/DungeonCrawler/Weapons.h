#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Weapons
{

	
	void loadTextures();
public:
	virtual void weaponType() { std::cout << "what is your weapon type" << std::endl; };
	virtual void damage()=0;
	virtual void animations()=0;
	virtual void traits()=0;
	
};

