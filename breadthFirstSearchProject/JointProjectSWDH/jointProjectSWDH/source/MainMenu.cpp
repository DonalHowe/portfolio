#include "..\header\MainMenu.h"
using namespace std;
MainMenu::MainMenu() {
	
	if (!m_backgroundTexture.loadFromFile("resources/img/menuBackground.png"))
	{
		cout << "cant load sprite" << endl;
	}
	m_background.setTexture(m_backgroundTexture);
	m_background.setPosition(0, 0);
	m_background.setScale(0.98, 0.98);
	songInitiliser();
	
	for (int i = 0; i < 4; i++)
	{
		menuButton[i].setSize(sf::Vector2f{ m_buttonWidth,m_buttonHeigth });
		menuButton[i].setPosition(buttonPositions);
		buttonPositions.y = buttonPositions.y + 150;
		if (i % 2 == 0)
		{
			menuButton[i].setFillColor(sf::Color::Red);
		}
		else {
			menuButton[i].setFillColor(sf::Color::Green);
		}
		
	}
	for (int i = 0; i < 2; i++) {
		chooseMapRects[i].setSize(m_mapSizes);
		
		
		
		chooseMapRects[i].setPosition(circlePositions);
		circlePositions.x = circlePositions.x + 450;
		
	}
	chooseMapRects[0].setFillColor(sf::Color::Red);
	chooseMapRects[0].setOutlineColor(sf::Color::Black);
	chooseMapRects[0].setOutlineThickness(5u);
	chooseMapRects[1].setFillColor(sf::Color::Green);
	chooseMapRects[1].setOutlineColor(sf::Color::Black);
	chooseMapRects[1].setOutlineThickness(5u);
	
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);

	t_window.draw(m_background);
	backgroundObject.render(t_window);
	for (int i = 0; i < 4; i++)
	{

		if (menuStateSwitcher == GameState::Start)
		{
			
			t_window.draw(menuButton[i]);
			t_window.draw(m_startGameText);
			t_window.draw(m_instructionstext);
			t_window.draw(m_creditsText);
			t_window.draw(m_mapsText);
			creditsSong.setVolume(0);
		}
		
		if (menuStateSwitcher == GameState::instructions)
		{
			backgroundObject.render(t_window);
			t_window.draw(m_returnText);
			t_window.draw(m_Instructionsdescription);
		
			creditsSong.setVolume(0);
		}
		if (menuStateSwitcher == GameState::credits)
		{
			
			backgroundObject.render(t_window);
			t_window.draw(m_returnText);
			t_window.draw(m_creditsDescrition);
			m_switchCredits = true;
			creditsSong.setVolume(10);
		
		}
		if (menuStateSwitcher == GameState::maps)
		{
			backgroundObject.render(t_window);
			t_window.draw(m_returnText);
			t_window.draw(m_mapDescrition);
			creditsSong.setVolume(0);
			for (int i = 0; i < 2; i++)
			{
				t_window.draw(chooseMapRects[i]);
			}
			t_window.draw(m_chooseGrassMap);
			t_window.draw(m_chooseSandMap);
		
		}
	}
	
}

// this swicthes the states for the menu only 
void MainMenu::update(double dt)
{
	backgroundObject.update(dt);

	

	chooseMap();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			stateSelected = false;


			menuStateSwitcher = GameState::Start;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stateSelected == false)
		{
			m_mouseClicked = true;
		}
		//for box one 
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 120 && mousePos.y < 240)
		{
			menuButton[0].setSize(sf::Vector2f{ m_animatedWidth,m_animatedHeight });
			menuButton[0].setOutlineColor(sf::Color::Cyan);
			menuButton[0].setOutlineThickness(3u);
		}
		else
		{
			menuButton[0].setSize(sf::Vector2f{ m_buttonWidth,m_buttonHeigth });
			menuButton[0].setOutlineThickness(0);
		}
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 120 && mousePos.y < 240 && m_mouseClicked == true)
		{

			menuStateSwitcher = GameState::gamePlay;
			cout << "gameplay" << endl;
			m_mouseClicked = false;
			stateSelected = true;
			nowGameplay = true;


		}
		//for box two 
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 270 && mousePos.y < 390)
		{
			menuButton[1].setSize(sf::Vector2f{ m_animatedWidth,m_animatedHeight });
			menuButton[1].setOutlineColor(sf::Color::Magenta);
			menuButton[1].setOutlineThickness(3u);
		}
		else
		{
			menuButton[1].setSize(sf::Vector2f{ m_buttonWidth,m_buttonHeigth });
			menuButton[1].setOutlineThickness(0);
		}
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 270 && mousePos.y < 390 && m_mouseClicked == true)
		{

			menuStateSwitcher = GameState::instructions;
			cout << "instructions " << endl;
			m_mouseClicked = false;
			stateSelected = true;
		}
		//for box three 
		if (mousePos.y > 420 && mousePos.y < 540 && mousePos.x > 100 && mousePos.x < 500)
		{
			menuButton[2].setSize(sf::Vector2f{ m_animatedWidth,m_animatedHeight });
			menuButton[2].setOutlineColor(sf::Color::Blue);
			menuButton[2].setOutlineThickness(3u);
		}
		else
		{
			menuButton[2].setSize(sf::Vector2f{ m_buttonWidth,m_buttonHeigth });
			menuButton[2].setOutlineThickness(0);
		}
		if (mousePos.y > 420 && mousePos.y < 540 && mousePos.x > 100 && mousePos.x < 500 && m_mouseClicked == true)
		{

			menuStateSwitcher = GameState::maps;
			cout << "maps " << endl;
			m_mouseClicked = false;
			stateSelected = true;
		}
		//for box four 
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 569 && mousePos.y)
		{
			menuButton[3].setSize(sf::Vector2f{ m_animatedWidth,m_animatedHeight });
			menuButton[3].setOutlineColor(sf::Color::Black);
			menuButton[3].setOutlineThickness(3u);
		}
		else
		{
			menuButton[3].setSize(sf::Vector2f{ m_buttonWidth,m_buttonHeigth });
			menuButton[3].setOutlineThickness(0);
		}
		if (mousePos.x > 100 && mousePos.x < 500 && mousePos.y > 569 && mousePos.y < 689 && m_mouseClicked == true)
		{
			menuStateSwitcher = GameState::credits;
			cout << "credits " << endl;
			m_mouseClicked = false;
			stateSelected = true;
		}
		songPlay();
	
	//cout << std::to_string(mousePos.x) << ", "<< std::to_string(mousePos.y) << endl;
}

void MainMenu::setupTexts(sf::Font &t_font)
{
	// sets up the font and strings for the menu
	if (!t_font.loadFromFile("resources/font/BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	//gameStart text
	m_startGameText.setFont(t_font);
	m_startGameText.setString("START THE GAME");
	m_startGameText.setPosition(100, 170);
	m_startGameText.setFillColor(sf::Color::Black);
	m_startGameText.setCharacterSize(50);

	m_chooseGrassMap.setFont(t_font);
	m_chooseGrassMap.setString("GRASS MAP");
	m_chooseGrassMap.setPosition(420, 510);
	m_chooseGrassMap.setFillColor(sf::Color::Black);
	m_chooseGrassMap.setCharacterSize(50);

	m_chooseSandMap.setFont(t_font);
	m_chooseSandMap.setString("SAND MAP");
	m_chooseSandMap.setPosition(900, 510);
	m_chooseSandMap.setFillColor(sf::Color::Black);
	m_chooseSandMap.setCharacterSize(50);

	

    m_instructionstext.setFont(t_font);
	m_instructionstext.setString("INSTRUCTIONS ");
	m_instructionstext.setPosition(100, 330);
	m_instructionstext.setFillColor(sf::Color::Black);
	m_instructionstext.setCharacterSize(50);


	m_mapsText.setFont(t_font);
	m_mapsText.setString("PICK A MAP");
	m_mapsText.setPosition(100, 450);
	m_mapsText.setFillColor(sf::Color::Black);
	m_mapsText.setCharacterSize(50);

	m_creditsText.setFont(t_font);
	m_creditsText.setString("CREDITS");
	m_creditsText.setPosition(100, 570);
	m_creditsText.setFillColor(sf::Color::Black);
	m_creditsText.setCharacterSize(50);

	
	m_returnText.setFont(t_font);
	m_returnText.setString("PRESS TAB TO LEAVE THE PAGE");
	m_returnText.setPosition(10, 100);
	m_returnText.setFillColor(sf::Color::Black);
	m_returnText.setCharacterSize(50);

	m_Instructionsdescription.setFont(t_font);
	m_Instructionsdescription.setString(" this is a top down 2D game  \n you play as a fox  \n kill all of the chickens \n  before the farmer reaches the chicken coup  \n and relises there is a fox there \n  and kills you \n press E by the food to increase your speed");
	m_Instructionsdescription.setPosition(250, 300);
	m_Instructionsdescription.setFillColor(sf::Color::Red);
	m_Instructionsdescription.setCharacterSize(50);

	m_mapDescrition.setFont(t_font);
	m_mapDescrition.setString(" please pick a map");
	m_mapDescrition.setPosition(550, 300);
	m_mapDescrition.setFillColor(sf::Color::Red);
	m_mapDescrition.setCharacterSize(50);

	m_creditsDescrition.setFont(t_font);
	m_creditsDescrition.setString(" by SEÁN WHELAN, \n c00250016 \n DÓNAL HOWE \n c00249662 \n Fox Mo-Cap: \n Bandit Whelan \n Russian Translation: \n David Jalisevs \n Chicken Mo-Cap: \n Shelly & Snoopy Howe \n Almost no chickens were harmed \n during the creation of this game \n R.I.P Dawids Chicken Roll...  ");
	m_creditsDescrition.setPosition(550, 900);
	m_creditsDescrition.setFillColor(sf::Color::Red);
	m_creditsDescrition.setCharacterSize(50);

}
bool MainMenu::getSandMap()
{
	return sandMapChosen;
}
bool MainMenu::getGrassMap()
{
	return grassMapChosen;
}
// controls the songs and credit movement in the menu
void MainMenu::songPlay()
{
	
	if (m_switchCredits == true&&m_songPlayedCredits==false)
	{
		creditsSong.play();
		
		m_songPlayedCredits = true;
		
	}
	
		m_creditsDescrition.move(0, -0.5);
		if (m_creditsDescrition.getPosition().y < -800)
		{
			m_creditsDescrition.setPosition(550, 900);
		}

	if (StartSong == true)
	{
		creditsSong.stop();
	}
	
}
// used to load the song
void MainMenu::songInitiliser()
{

	if (!creditsBuffer.loadFromFile("resources/music/creditsSong.wav"))
	{
		cout << "cant load song file" << endl;
	}
	creditsSong.setBuffer(creditsBuffer);
	
}

void MainMenu::chooseMap()
{
	
	// grass map
	if (menuStateSwitcher == GameState::maps)
	{
		std::cout << mousePos.x << "," << mousePos.y << std::endl;
		if (mousePos.x > 395 && mousePos.x < 703 && mousePos.y > 410 && mousePos.y < 625&&mapChosen==false)
		{
			
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				cout << "choose grass " << endl;
				mapChosen = true;
				grassMapChosen = true;
			}
			

		}
		
		if (mousePos.x > 845 && mousePos.x < 1152 && mousePos.y > 410 && mousePos.y < 625 &&mapChosen == false)
		{
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				cout << "choose sand " << endl;
				grassMapChosen = false;
				sandMapChosen = true;
				mapChosen = true;
			}
		}
		//grass map bigger
		if (mousePos.x > 395 && mousePos.x < 703 && mousePos.y > 410 && mousePos.y < 625 && mapChosen == false)
		{
			chooseMapRects[0].setSize(sf::Vector2f{ m_mapSizes.x + 30, m_mapSizes.y + 30 });

		}
		else
		{
			chooseMapRects[0].setSize(sf::Vector2f{ m_mapSizes });

		}
		// sand map bigger
		if (mousePos.x > 845 && mousePos.x < 1152 && mousePos.y > 410 && mousePos.y < 625 && mapChosen == false)
		{
			chooseMapRects[1].setSize(sf::Vector2f{ m_mapSizes.x + 30, m_mapSizes.y + 30 });
			
		}
		else
		{
			chooseMapRects[1].setSize(sf::Vector2f{ m_mapSizes });

		}
	}
}





