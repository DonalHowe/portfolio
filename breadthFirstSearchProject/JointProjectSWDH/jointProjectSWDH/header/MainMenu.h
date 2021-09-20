#pragma once
#include "GameState.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "ScreenSize.h"
#include "ScrollingBackGround.h"
#include "SFML/Audio.hpp"
class MainMenu
{
public:
	// constructor and treh resto of teh public functions
	MainMenu();
	void render(sf::RenderWindow &t_window);
	void update(double dt);
	bool nowGameplay = false;
	void setupTexts(sf::Font &t_font);
	ScrollingBackGround backgroundObject;
	
	GameState menuStateSwitcher{ GameState::Start };
	sf::Sprite m_background;

	bool getSandMap();
	bool getGrassMap();
private:

	bool sandMapChosen = false;
	bool grassMapChosen = true;
	// private functions and vriables
	// song function and variables to play music
	void songPlay();
	bool mapChosen=false;
	sf::Vector2f m_mapSizes{ 300,200 };
	// the sound music
	sf::Sound  creditsSong;
	sf::SoundBuffer creditsBuffer;
	sf::RectangleShape chooseMapRects[2];
	bool StartSong = false;
	bool m_switchCredits = false;
	bool m_songPlayedCredits = false;
	void songInitiliser();
	// track the mouse placement
	sf::Vector2i mousePos;
	// the texts which are displayed throughout the menu
	sf::Text m_startGameText;
	sf::Text m_mapsText;
	sf::Text m_instructionstext;
	sf::Text m_creditsText;
	sf::Text m_returnText;
	sf::Text m_Instructionsdescription;
	sf::Text m_creditsDescrition;
	sf::Text m_mapDescrition;
	sf::Text m_chooseSandMap;
	sf::Text m_chooseGrassMap;
	void chooseMap();

	sf::Font m_textFont;
	// teh rect shapes which are identifiers of teh menu tabs
	sf::RectangleShape menuButton[4];
	sf::Vector2f circlePositions{ 400,420 };
	sf::Vector2f buttonPositions{ 100,120 };
	sf::Texture m_backgroundTexture;
	sf::FloatRect boundingBox;



	// the bounds for where to switch teh states and bools etc
	int m_topOffset = 50;
    int	m_verticalSpacing = 100;
    float m_buttonWidth = 400;
	float m_buttonHeigth = 120;
	float m_animatedWidth = 420;
	float m_animatedHeight = 140;

	int m_leftTopOffset = (ScreenSize::s_height - ScreenSize::s_width) / 2;      //(Game::s_screenWidth - m_buttonWidth)/2; after game is merged
	

	bool m_mouseClicked = false;
	bool stateSwitched = false;
	bool stateSelected = false;
	
};

