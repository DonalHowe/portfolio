#pragma once
#include <SFML/Graphics.hpp>
#include "GameStates.h"
#include <iostream>
#include "Player.h"
#include <vector>
#include "ScreenSize.h"
#include "Inventory.h"
#include <SFML/Audio.hpp>

class MainMenu
{
	
	Player m_player;
	//Shop m_shop;
	sf::Texture InventoryBGtexture;
	sf::RectangleShape m_rect;
	sf::RectangleShape m_newRect;
	std::vector<sf::RectangleShape> m_RectVec;
	sf::Vector2f m_rectPos{ 10,10 };
	sf::Vector2f m_rectSize{ 200,100 };
	//sf::Font strFont;
	sf::Text m_playText;
	sf::Text m_instructionsText;
	sf::Text m_CreditsText;
	sf::Text m_ShopText;
	sf::Text m_backText;
	sf::Text m_finalCreditsText;
	sf::Sprite menuSprite;
	sf::Texture menuTexture;
	sf::Text m_menuTitle;
	sf::Text m_levelEditorText;
	sf::SoundBuffer m_musicBuffer;
	sf::Sound m_music;
	sf::Sprite creditsSprite;
	sf::Texture creditsTexture;



	bool musicPlayed = false;
	int id = 0;
	int colorTimer;
	sf::Vector2i m_mousePos;
	void creditScroll();
	bool selectLevelEditor = false;
	sf::RectangleShape editingDisabledBox;
	sf::RectangleShape editingEnabledBox;
	sf::Text m_enableEditor;
	sf::Text m_disableEditor;
	void setupEditor();
	void manageEditor();

	const static int XposLeft = 10;
	const static int XposRight = 210;
	void stateChecker();
	void playMusic();
	
	bool isTutorial = false;
	bool isMain = false;
	bool isStartGame = false;
public:
	GameStates m_gstates = { GameStates::Menu };
	MenuStates m_menuSwitcher = { MenuStates::Main };
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	void SetupSprites();
	void musicInitiliser();
	MainMenu(sf::Font  & t_font);
	bool getEditor();


};

