#include "Inventory.h"




void Inventory::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_Sprite);
	t_window.draw(m_text);
	/*for (int i = 0; i < MAX_SLOTS; i++)
	{
		t_window.draw(m_rectVec.at(i));

	}
	*/
	if (gotSword == true)
	{
		t_window.draw(m_swordSprite);
	}


	if (gotKey == true)
	{
		t_window.draw(m_keySprite);
	}
	if (gotAxe == true)
	{
		t_window.draw(m_axeSprite);
	}
	
}

bool Inventory::GetGotKeyBoolean()
{
	return gotKey;
}

void Inventory::setupSprites(std::string keyLocation,  std::string t_swordLocation,std::string t_axeLocation)
{
	if (!m_keyTexture.loadFromFile(keyLocation))
	{
		std::cout << "cant load sprite cage" << std::endl;

	}
	if (!m_playerTexture.loadFromFile("rescources/images/USED-IMAGES/inventoryBG.jfif"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	//background sprite
	m_Sprite.setTexture(m_playerTexture);
	m_Sprite.setScale(4.5, 5);
	m_Sprite.setPosition(-100, m_Sprite.getPosition().y);
	//loading the key sprite
	m_keySprite.setTexture(m_keyTexture);
	m_keySprite.setPosition(100, 100);
	
	m_keySprite.setTextureRect(sf::IntRect{ 32, 0, 32 , 32 });
	m_keySprite.setScale(4, 4);

	if (!m_swordTexture.loadFromFile(t_swordLocation))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	m_swordSprite.setTexture(m_swordTexture);
	m_swordSprite.setPosition(350, 100);
	m_swordSprite.setScale(1, 1);

	if (!m_axeTexture.loadFromFile(t_axeLocation))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	m_axeSprite.setTexture(m_axeTexture);
	m_axeSprite.setTextureRect(sf::IntRect{ 20, 0, 500 , 420 });
	m_axeSprite.setPosition(650, 100);
	m_axeSprite.setScale(0.4, 0.4);
	
	
}
	


void Inventory::collectedItems(bool t_keyCollected,bool t_swordCollected,bool t_axeCollected)
{
	
	gotKey = t_keyCollected;
	gotSword = t_swordCollected;
	gotAxe = t_axeCollected;
	
}

Inventory::Inventory()
{
	m_rect.setSize(sf::Vector2f{ 200,200 });
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Red);
	m_rect.setOutlineThickness(2u);

	pos.y = yPos;
	pos.x = xPos;
	m_rect.setPosition(pos);
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_rect.setPosition(pos);
		m_rectVec.push_back(m_rect);
		pos.x += m_rect.getSize().x;
		if (m_rectVec.at(i).getPosition().x > 400)
		{
			pos.y += m_rect.getSize().y;
			pos.x = xPos;
		}

	}
	

}

Inventory::Inventory(const Inventory& other)
{
	m_Sprite=other.m_Sprite;	//background sprite
	 m_playerTexture=other.m_playerTexture;	//BACKGROUND TEXTURE
	 m_text=other.m_text;	//text for the inventory
	 m_rectVec=other.m_rectVec;	// vector of sd::rectShapes
	 m_rect=other.m_rect;
	 pos=other.pos;
	m_keyTexture=other.m_keyTexture;
	m_keySprite=other.m_keySprite;

	 xPos = other.xPos;
	 yPos = other.yPos;
	 gotKey = other.gotKey;
	 
}

void Inventory::setupText(sf::Text t_text)
{
	m_text = t_text;

}

