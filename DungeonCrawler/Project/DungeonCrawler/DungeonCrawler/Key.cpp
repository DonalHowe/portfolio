#include "Key.h"


Key::Key()
{
}

void Key::setupSprite(sf::Texture& t_texture,sf::Vector2f t_position, sf::Vector2f t_scale)
{
	m_Sprite.setTexture(t_texture);
	m_Sprite.setPosition(t_position);
	m_Sprite.setScale(t_scale);
}

void Key::render(sf::RenderWindow& t_window )
{
	t_window.draw(m_Sprite);
}

void Key::update(double dt)
{
	m_FrameIncrement = 0.027f; // how fast 

	m_FrameCounter += m_FrameIncrement;
	m_Frame = static_cast<int>(m_FrameCounter) % 12; // change valuues later to see the difference 
	//bossSprite.setTextureRect(sf::IntRect{ m_Frame * 191, 322, 191 , 161 }); // for 3 sprites
	m_Sprite.setTextureRect(sf::IntRect{ m_Frame * 32, 0, 32 , 32 });
}
