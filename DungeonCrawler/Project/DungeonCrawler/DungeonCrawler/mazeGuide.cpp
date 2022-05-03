#include "mazeGuide.h"

void mazeGuide::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

void mazeGuide::update(double dt)
{
}

mazeGuide::mazeGuide()
{
	setupGuideSprite();
}

mazeGuide::~mazeGuide()
{
}

void mazeGuide::movement(sf::Vector2f pos)
{
	if (m_shape.getPosition().x > pos.x)
	{
		m_shape.move(-0.5, 0);
	}
	else if (m_shape.getPosition().x < pos.x)
	{
		m_shape.move(0.5, 0);
	}
	else if (m_shape.getPosition().y > pos.y)
	{
		m_shape.move(0, -0.5);
	}
	if (m_shape.getPosition().y < pos.y)
	{
		m_shape.move(0, 0.5);
	}
}

void mazeGuide::setupGuideSprite()
{
	m_shape.setRadius(14u);
	m_shape.setPosition(100, 100);
	m_shape.setFillColor(sf::Color::White);

}
