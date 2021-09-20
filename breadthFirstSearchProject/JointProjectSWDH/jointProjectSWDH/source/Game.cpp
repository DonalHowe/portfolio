#include "..\header\Game.h"


//author : Donal Howe
//author : Sean Whelan

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////


Game::Game() : m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);
	initilisefileLoads();
	
	
	chickenEnemies[0].theFeed.setPosition(myGrid.gridVector.at(3).at(6).m_Pos);
	chickenEnemies[1].theFeed.setPosition(myGrid.gridVector.at(4).at(4).m_Pos);
	chickenEnemies[2].theFeed.setPosition(myGrid.gridVector.at(2).at(3).m_Pos);
	chickenEnemies[3].theFeed.setPosition(myGrid.gridVector.at(5).at(7).m_Pos);
	chickenEnemies[4].theFeed.setPosition(myGrid.gridVector.at(8).at(8).m_Pos);
	chickenEnemies[5].theFeed.setPosition(myGrid.gridVector.at(6).at(4).m_Pos);

}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}


// this is the function we are going to use to create the map nodes


void Game::initilisefileLoads()
{
	//loading font
	if (!m_font.loadFromFile("resources/font/BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	menuSystem.setupTexts(m_font);
	m_gameLostText.setFont(m_font);
	m_gameLostText.setPosition(100, 400);
	m_gameLostText.setFillColor(sf::Color::Green);
	m_gameLostText.setCharacterSize(45u);
	m_gameLostText.setOutlineColor(sf::Color::Magenta);
	m_gameLostText.setOutlineThickness(5u);
	m_gameLostText.setString(" UNLUCKY YOU LOST THE FARMER REALISED THE CHICKENS ARE MISSING AND KILLED YOU ");

	m_winText.setFont(m_font);
	m_winText.setPosition(300, 400);
	m_winText.setFillColor(sf::Color::Red);
	m_winText.setCharacterSize(45u);
	
	m_winText.setOutlineColor(sf::Color::Cyan);
	m_winText.setOutlineThickness(5u);
	m_winText.setString(" CONGRATS YOU WIN YOU KILLED ALL OF THE CHICKENS ");

	
	chickensLeft.setFont(m_font);
	chickensLeft.setPosition(1000, 50);
	chickensLeft.setFillColor(sf::Color::Blue);
	chickensLeft.setOutlineColor(sf::Color::Black);
	chickensLeft.setOutlineThickness(5u);
	chickensLeft.setCharacterSize(45u);
	
	
	if (!m_grassTexture.loadFromFile("resources/img/farmBase.jpg"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	m_grassBackgroundSprite.setTexture(m_grassTexture);
	m_grassBackgroundSprite.setPosition(0, 0);
	m_grassBackgroundSprite.setScale(2.5, 2.5);

	if (!m_sandTexture.loadFromFile("resources/img/SandBase.jpg"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	m_sandBackground.setTexture(m_sandTexture);
	m_sandBackground.setPosition(0, 0);
	m_sandBackground.setScale(2.5, 2.5);

	if (!m_coupTexture.loadFromFile("resources/img/chickenCoup.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	m_chickenCoup.setTexture(m_coupTexture);
	float yValueCoup = myGrid.gridVector.at(myGrid.getEndRow()).at(myGrid.getEndCol()).m_Pos.y - 100;
	float xValueCoup = myGrid.gridVector.at(myGrid.getEndRow()).at(myGrid.getEndCol()).m_Pos.x;
	m_chickenCoup.setPosition(xValueCoup, yValueCoup);
	m_chickenCoup.setScale(1.0, 0.7);

}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;

		case sf::Keyboard::Space:

			
			break;
		
		default:
			break;
		}
	}
}


////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	//simply to switch to the gameplay7 state from menu does not control gameplay sub sates ie endign mid game etc
	if (menuSystem.nowGameplay == true)
	{
		m_gameState = GameState::gamePlay;
	
	}

	if (m_gameState == GameState::Start)
	{
		menuSystem.update(dt);
	
	}
	if (m_gameState == GameState::gamePlay )
	{
		myPlayer.update(dt);

		for (int i = 0; i < max_chickens; i++)
		{
		chickenEnemies[i].update(dt);
		}
		farmer.update(dt);
	
		chickensLeft.setString("CHICKEN LIVES :" + std::to_string(chickenDead));
	
		particleSystem.update();

		collisionChecker();
		
		
	}
	
	
	

}


////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	
	if (m_gameState == GameState::gamePlay)
	{
		if (menuSystem.getGrassMap() == true)
		{
			m_window.draw(m_grassBackgroundSprite);
		}
		else if (menuSystem.getSandMap() == true)
		{
			//display the sand map
			m_window.draw(m_sandBackground);
		}
			
			
			myGrid.render(m_window);
			m_window.draw(m_chickenCoup);
			myPlayer.draw(m_window);
			for (int i = 0; i < max_chickens; i++)
			{
				chickenEnemies[i].render(m_window);
			}
			particleSystem.Draw(m_window);
			farmer.render(m_window);
			m_window.draw(chickensLeft);

	}
	if (m_gameState == GameState::Start) {
		menuSystem.render(m_window);
	}

	if (m_gameState == GameState::ending) {
		m_window.draw(menuSystem.m_background);
		m_window.draw(m_gameLostText);

	}
	if (m_gameState == GameState::winning) {
		m_window.draw(menuSystem.m_background);
		m_window.draw(m_winText);

	}


	m_window.display();
};

void Game::collisionChecker()
{
	for (int i = 0; i < max_chickens; i++)
	{
		if (CollisionDetector::collisionProjectileToTarget(myPlayer.getBody(), chickenEnemies[i].getBody()))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				
				chickenEnemies[i].killChicken();
				particleSystem.Initialise(myPlayer.getBody().getPosition());
				chickenDead--;
			}
		}

		if (CollisionDetector::collisionProjectileToTarget(myPlayer.getBody(), chickenEnemies[i].theFeed.getSprite()))
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				std::cout << "you have eaten foxy snakcs" << std::endl;
				chickenEnemies[i].theFeed.setPosition(moveFood);
				myPlayer.setPlayerSpeed(myPlayer.getPlayerSpeed() + .25);
			}
			
		}

	}

	// this is the collisions for the chickien coup and the player as a win and loss condition
	if (m_chickenCoup.getGlobalBounds().intersects(farmer.getFarmer().getGlobalBounds()))
	{
		m_gameState = ::GameState::ending;
	}
	// this is the conditiopn for the player to win the game i.e kill all of the chickens 
	if (chickenDead == 0)
	{
		m_gameState = ::GameState::winning;
	}

}



