#include "MainMenu.h"

void MainMenu::creditScroll()
{
	m_finalCreditsText.move(0, 0.25);
	if (m_finalCreditsText.getPosition().y > ScreenSize::screen_height)
	{
		m_finalCreditsText.setPosition(200, 200);
	}
}

void MainMenu::setupEditor()
{
	editingDisabledBox.setSize(sf::Vector2f{ 300,300 });
	editingDisabledBox.setFillColor(sf::Color::Magenta);
	editingEnabledBox.setFillColor(sf::Color::Blue);
	editingEnabledBox.setPosition(100, 300);
	editingDisabledBox.setPosition(600, 300);
	editingEnabledBox.setSize(sf::Vector2f{ 300,300 });
	
}

void MainMenu::manageEditor()
{
	if (m_mousePos.x > 100 && m_mousePos.x < 400)
	{
		
		editingEnabledBox.setOutlineColor(sf::Color::Green);
		editingEnabledBox.setOutlineThickness(10u);
		if (m_mousePos.y > 267 && m_mousePos.y < 540)
		{
			
			// level Editor enabled
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				selectLevelEditor = true;
			}

		}
	}
	else
	{
		editingEnabledBox.setOutlineColor(sf::Color::Transparent);
	}
	if (m_mousePos.x > 600 && m_mousePos.x < 900)
	{
		editingDisabledBox.setOutlineColor(sf::Color::Cyan);
		editingDisabledBox.setOutlineThickness(10u);
		if (m_mousePos.y > 267 && m_mousePos.y < 540)
		{
			editingEnabledBox.setSize(sf::Vector2f{ 350,300 });
			// level Editor enabled
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				selectLevelEditor = false;
			}
		}
	}
	else
	{
		editingDisabledBox.setOutlineColor(sf::Color::Transparent);
	}
}

void MainMenu::stateChecker()
{
	//play button
	
	if (m_mousePos.x > XposLeft && m_mousePos.x < XposRight)
	{	
		if (m_mousePos.y > 10 && m_mousePos.y < 100)
		{


		

			m_RectVec.at(0).setFillColor(sf::Color::Blue);
			m_RectVec.at(0).setOutlineColor(sf::Color::Magenta);
			m_RectVec.at(0).setOutlineThickness(5u);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				m_menuSwitcher = MenuStates::StartGame;
			}
			
		}
		else
		{
			m_RectVec.at(0).setFillColor(sf::Color::Red);
			m_RectVec.at(0).setOutlineThickness(0);
		}
	}
	
	
	//inventory
	 if (m_mousePos.x > XposLeft && m_mousePos.x < XposRight)
	{
		
		if (m_mousePos.y > 143 && m_mousePos.y < 245 )
		{
			m_RectVec.at(1).setFillColor(sf::Color::Black);
			m_RectVec.at(1).setOutlineColor(sf::Color::Green);
			m_RectVec.at(1).setOutlineThickness(5u);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				m_menuSwitcher = MenuStates::LevelEditor;
			}
			
		}
		else
		{
			m_RectVec.at(1).setFillColor(sf::Color::Red);
			m_RectVec.at(1).setOutlineThickness(0);
		}
	}
	 
	 
	 //instructions
     if (m_mousePos.x > XposLeft && m_mousePos.x < XposRight)
	{
		
		if (m_mousePos.y > 278 && m_mousePos.y < 365)
		{
			m_RectVec.at(2).setFillColor(sf::Color::Cyan);
			m_RectVec.at(2).setOutlineColor(sf::Color::Black);
			m_RectVec.at(2).setOutlineThickness(5u);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				m_menuSwitcher = MenuStates::tutorial;
			}
			
		}
		else
		{
			m_RectVec.at(2).setFillColor(sf::Color::Red);
			m_RectVec.at(2).setOutlineThickness(0);
		}
	}
	
	 // credits
	 if (m_mousePos.x > XposLeft && m_mousePos.x < XposRight)
	{
		
		 if (m_mousePos.y > 400 && m_mousePos.y < 505 )
		{

			 m_RectVec.at(3).setFillColor(sf::Color::Magenta);
			 m_RectVec.at(3).setOutlineColor(sf::Color::Cyan);
			 m_RectVec.at(3).setOutlineThickness(5u);
			 if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			 {
				
				 m_menuSwitcher = MenuStates::Credits;
			 }
			
		}
		 else
		 {
			 m_RectVec.at(3).setFillColor(sf::Color::Red);
			 m_RectVec.at(3).setOutlineThickness(0);
		 }
	}
	
	 if (m_menuSwitcher != MenuStates::Main)
	 {
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				 m_menuSwitcher = MenuStates::Main;
			 }
		 
	 }
}

void MainMenu::playMusic()
{
	m_music.play();
	musicPlayed == true;
}

void MainMenu::musicInitiliser()
{
	if (!m_musicBuffer.loadFromFile("rescources/sound/menuMusic.wav"))
	{
		std::cout << "cant load song file" << std::endl;
	}
	m_music.setBuffer(m_musicBuffer);
	
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	 m_mousePos = sf::Mouse::getPosition(t_window);
	if (m_menuSwitcher == MenuStates::Main)
	{
		t_window.draw(menuSprite);
		for (int i = 0; i < 4; i++)
		{
			t_window.draw(m_RectVec.at(i));
		}
		t_window.draw(m_playText);
		t_window.draw(m_instructionsText);
		t_window.draw(m_ShopText);
		t_window.draw(m_CreditsText);
		t_window.draw(m_menuTitle);
		
	}
	else if (m_menuSwitcher == MenuStates::LevelEditor)
	{
		t_window.draw(creditsSprite);
		t_window.draw(m_levelEditorText);
		t_window.draw(editingDisabledBox);
		t_window.draw(editingEnabledBox);
		t_window.draw(m_enableEditor);
		t_window.draw(m_disableEditor);
	}
	else if (m_menuSwitcher == MenuStates::Credits)
	{
		t_window.draw(creditsSprite);
		t_window.draw(m_backText);
		t_window.draw(m_finalCreditsText);
	}
	else if (m_menuSwitcher == MenuStates::tutorial)
	{
		t_window.draw(menuSprite);
		t_window.draw(m_player.GetSprite());
		t_window.draw(m_backText);
		
	}
	else if (m_menuSwitcher == MenuStates::StartGame)
	{
		m_gstates = GameStates::LevelOne;
	}
	
}

void MainMenu::update(double dt)
{
	//std::cout << "in menu" << std::endl;

	stateChecker();
	std::cout <<" THIS IS X " << m_mousePos.x <<"THIS IS Y " << m_mousePos.y << std::endl;


	if (m_menuSwitcher == MenuStates::Main)
	{
		colorTimer++;
		if (musicPlayed == false)
		{
			playMusic();
		}
		if (colorTimer < 100)
		{
			
			m_menuTitle.setOutlineColor(sf::Color::Red);
			m_menuTitle.setFillColor(sf::Color::Cyan);
		}
		else if (colorTimer > 700 && colorTimer < 1300)
		{
			
			m_menuTitle.setFillColor(sf::Color::Blue);
			m_menuTitle.setOutlineColor(sf::Color::Black);
		}
		else if (colorTimer > 1300 && colorTimer < 1900)
		{
			
			m_menuTitle.setFillColor(sf::Color::Magenta);
			m_menuTitle.setOutlineColor(sf::Color::Green);
		}
		if (colorTimer > 2500)
		{
			colorTimer = 0;
		}
		std::cout << colorTimer << std::endl;
	}
	else if (m_menuSwitcher == MenuStates::LevelEditor)
	{
		musicPlayed = false;
		manageEditor();
	}
	else if (m_menuSwitcher == MenuStates::Credits)
	{
		creditScroll();
		musicPlayed = false;
	}
	else if (m_menuSwitcher == MenuStates::tutorial)
	{
		musicPlayed = false;
		m_player.Walkingmovement();

		
	}
	else if (m_menuSwitcher == MenuStates::StartGame)
	{
		musicPlayed = false;
	}
}

void MainMenu::SetupSprites()
{
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setSize(sf::Vector2f{ m_rectSize });
	
	for (int i = 0; i < 4; i++)
	{
		
		m_rect.setPosition(m_rectPos);
		m_rectPos.y += 150;
		m_RectVec.push_back(m_rect);
	}
	int i = 0;

	if (!menuTexture.loadFromFile("rescources/images/USED-IMAGES/game_background_4.png"))
	{
		std::cout << "cant load sprite" << std::endl;

	}
	if (!creditsTexture.loadFromFile("rescources/images/USED-IMAGES/creditsPng.png"))
	{
		std::cout << "cant load sprite" << std::endl;

	}
	creditsSprite.setTexture(creditsTexture);
	creditsSprite.setPosition(ScreenSize::screen_width / 2, ScreenSize::screen_height / 2);
	creditsSprite.setOrigin(creditsSprite.getGlobalBounds().width / 2, creditsSprite.getGlobalBounds().height / 2);
	creditsSprite.setScale(sf::Vector2f(1.55f, 1.95f));



	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(ScreenSize::screen_width / 2, ScreenSize::screen_height / 2);
	menuSprite.setOrigin(menuSprite.getGlobalBounds().width / 2, menuSprite.getGlobalBounds().height / 2);
	menuSprite.setScale(sf::Vector2f(.35f, .35f));


	
}

MainMenu::MainMenu(sf::Font & m_font )
{
	SetupSprites();
	setupEditor();
	
	//m_shop.setupText(m_font);
	m_playText.setFont(m_font);
	m_instructionsText.setFont(m_font);
	m_ShopText.setFont(m_font);
	m_CreditsText.setFont(m_font);
	m_backText.setFont(m_font);
	m_finalCreditsText.setFont(m_font);
	m_menuTitle.setFont(m_font);
	m_levelEditorText.setFont(m_font);
	m_levelEditorText.setCharacterSize(50u);
	m_levelEditorText.setPosition(200, 100);
	m_levelEditorText.setString("this is the level Editor selector");
	m_menuTitle.setPosition(200, 100);
	m_menuTitle.setString("   Dungeon Crawler \n   The Game ");
	m_menuTitle.setCharacterSize(110u);
	m_menuTitle.setOutlineThickness(5u);
	m_enableEditor.setPosition(100, 450);
	m_enableEditor.setCharacterSize(50u);
	m_enableEditor.setString("enable editing ");
	m_enableEditor.setFont(m_font);

	m_disableEditor.setPosition(600, 450);
	m_disableEditor.setCharacterSize(50u);
	m_disableEditor.setString("disable editing ");
	m_disableEditor.setFont(m_font);

	
	m_instructionsText.setString("Instructions");
	m_ShopText.setString("Level editor");
	m_CreditsText.setString("Credits");
	m_playText.setString("Play");
	m_backText.setString(" Davids says press tab to go back");
	m_finalCreditsText.setString(" A game by Davids Jalisevs C00239534 and\n Donal Howe C00249662. \n This is the final credits. \n Thank you for playing our game \n coming soon to a dungeon near you");
	m_finalCreditsText.setFillColor(sf::Color::Magenta);
	m_finalCreditsText.setOutlineColor(sf::Color::Cyan);
	m_finalCreditsText.setOutlineThickness(2u);
	m_finalCreditsText.setPosition(200, 200);
	m_finalCreditsText.setCharacterSize(40u);
	m_backText.setPosition(100, 10);
	m_playText.setPosition(XposLeft + 15, 30);
	m_ShopText.setPosition(XposLeft + 15, 199);
	m_instructionsText.setPosition(XposLeft + 15, 325);
	m_CreditsText.setPosition(XposLeft + 15, 460);

	
	
}

bool MainMenu::getEditor()
{
	return selectLevelEditor;
}
