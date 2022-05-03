#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Sword.h"
class Inventory
{
	
	sf::Sprite m_Sprite;	//background sprite
	sf::Texture m_playerTexture;	//BACKGROUND TEXTURE
	sf::Text m_text;	//text for the inventory
	std::vector<sf::RectangleShape> m_rectVec;	// vector of sd::rectShapes
	sf::RectangleShape m_rect;
	sf::Vector2f pos;
	sf::Texture m_keyTexture;
	sf::Sprite m_keySprite;
	
	sf::Sprite m_swordSprite;
	sf::Texture m_swordTexture;

	sf::Sprite m_axeSprite;
	sf::Texture m_axeTexture;


	float xPos=120;
	float yPos=100;
	
	static const int MAX_SLOTS = 9;
	bool gotKey = false;
	bool gotSword = false;
	bool gotAxe = false;

public:
	
	void setupSprites(std::string keyLocation,std::string t_swordLocation,std::string t_axeLocation);
	void render(sf::RenderWindow& t_window);
	bool GetGotKeyBoolean();
	void collectedItems( bool t_keyCollected ,bool t_swordCollected,bool t_axeCollected);
	Inventory();
	Inventory(const Inventory  &other);
	void setupText(sf::Text t_text);

	
};

