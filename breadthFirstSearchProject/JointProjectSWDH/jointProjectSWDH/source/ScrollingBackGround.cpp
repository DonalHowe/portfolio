#include "..\header\ScrollingBackGround.h"

ScrollingBackGround::ScrollingBackGround()
{
	initilise();
}

void ScrollingBackGround::initilise()
{
	
	for (int i = 0; i < maxBoxes; i++)
	{
		backGroundArray[i].setSize(sf::Vector2f{ 100,100 });
		backGroundArray[i].setFillColor(sf::Color::Magenta);
		
		
		backGroundArray[i].setPosition(boxPos);
		boxPos.x += 150;
		
	}
}

void ScrollingBackGround::update(double dt)
{
	for (int i = 0; i < maxBoxes; i++)
	{
		backGroundArray[i].move(-.9, 0);
		if (backGroundArray[i].getPosition().x <= 0)
		{
			boxPos.y -= 100;
			boxPos.x = ScreenSize::s_width;
			backGroundArray[i].setPosition(boxPos);
			if (backGroundArray[i].getPosition().y <= 0)
			{
				boxPos = startPos;
			}


		}
	}
	
}

void ScrollingBackGround::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < maxBoxes; i++)
	{
		t_window.draw(backGroundArray[i]);
	}
	
}
