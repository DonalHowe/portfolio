#include "..\header\chickenFeed.h"




sf::Sprite chickenFeed::getSprite()
{
	return m_feedSprite;
}

void chickenFeed::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_feedSprite.setPosition(m_position);

}

void chickenFeed::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_feedSprite);
}




