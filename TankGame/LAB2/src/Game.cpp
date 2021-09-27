#include "Game.h"


//author : donal howe

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game() : m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default), m_tank(m_texture, m_wallSprites),
m_enemies(m_wallSprites), m_aiTankOne(m_texture, m_wallSprites),m_hud(m_font)
{

	m_window.setVerticalSyncEnabled(true);
	int currentLevel = 1;
	// it will create an exceptionif the level loading fails
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (const std::exception& e)
	{
		std::cout << "level loading failure" << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	// Load the player tank
	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_backGroundTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	if (!m_fuelTexture.loadFromFile("./resources/images/fuel.png"))
	{
		//
	}
	m_fuel.setTexture(m_fuelTexture);
	m_fuel.setPosition(300, 300);
	m_fuel.setScale(.05, .05);

	if (!m_prizeTexture.loadFromFile("./resources/images/prize.png"))
	{
		//
	}
	m_prize.setTexture(m_prizeTexture);
	m_prize.setScale(.1, .1);
	m_prize.setPosition(1300, 50);
	
	if (!m_font.loadFromFile("./resources/images/BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	if (!m_enemyDeathSoundABuffer.loadFromFile("./resources/images/enemyDeath.wav"))
	{
		std::cout << "error loading sound" << std::endl;
	}
	
	m_enemyDeathSound.setBuffer(m_enemyDeathSoundABuffer);
	

	tank_fuel_text.setFont(m_font);
	tank_fuel_text.setPosition(400, 50);
	tank_fuel_text.setFillColor(sf::Color::Black);
	tank_fuel_text.setCharacterSize(30);
	tank_fuel_text.setFillColor(sf::Color::Blue);
	clockTextTimer.setFont(m_font);

	clockTextTimer.setPosition(100, 50);
	clockTextTimer.setFillColor(sf::Color::White);
	clockTextTimer.setCharacterSize(30);

	ScoreText.setFont(m_font);

	ScoreText.setPosition(200, 50);
	ScoreText.setFillColor(sf::Color::Red);
	ScoreText.setCharacterSize(30);

	accuracyText.setFont(m_font);

	accuracyText.setPosition(500, 300);
	accuracyText.setFillColor(sf::Color::White);
	accuracyText.setCharacterSize(30);

	//setting up the tank line
	

	gameOver.setFont(m_font);
	gameOver.setString("Gameover out of time");
	gameOver.setPosition(500, 500);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setCharacterSize(30);

	gameWin.setFont(m_font);
	gameWin.setString("CONGRATS YOU WON");
	gameWin.setPosition(500, 500);
	gameWin.setFillColor(sf::Color::White);
	gameWin.setCharacterSize(30);


	m_BackGroundSprite.setTexture(m_backGroundTexture);
	m_BackGroundSprite.setPosition(ScreenSize::s_width / 2, ScreenSize::s_height / 2);
	m_BackGroundSprite.setOrigin(ScreenSize::s_width / 2, ScreenSize::s_height / 2);
	generateWalls();

	m_enemies.setDuration(m_level.m_enemies.at(0).m_duration, m_level.m_enemies.at(1).m_duration, m_level.m_enemies.at(2).m_duration, m_level.m_enemies.at(3).m_duration);
	m_tank.setPosition(m_level.m_tank.m_postion);

	m_directionTriangle.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_directionTriangle.setFillColor(sf::Color::Red);
	m_directionTriangle.setOrigin(m_directionTriangle.getGlobalBounds().width / 2, m_directionTriangle.getGlobalBounds().height / 2);

	m_aiTankOne.init(m_level.m_aiTank.m_postion);
	
    using std::placeholders::_1;
	srand(time(nullptr));
   possibleLocation=rand() % 4 + 1;
   if (possibleLocation == 1)
   {
	   goalLocation.setPosition(locationOne);
   }
   else if (possibleLocation == 2)
   {
	   goalLocation.setPosition(locationTwo);
   }
   else if (possibleLocation == 3)
   {
	   goalLocation.setPosition(locationThree);
   }
   else if (possibleLocation == 4)
   {
	   goalLocation.setPosition(locationFour);
   }

	m_funcApplyDamage = std::bind(&TankAi::applyDamage, &m_aiTankOne, _1);
	goalLocation.setSize(sf::Vector2f{ 50,50 });
	goalLocation.setFillColor(sf::Color::Green);

	
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

void Game::collsionDectection()
{
	//for (int i = 0; i < m_enemies.MAX_ENEMIES; i++)
	//{
	//	if (m_tank.tankBullet.bulletSprite.getGlobalBounds().intersects(m_enemies.m_enemiesArray.at(i).getGlobalBounds()))
	//	{
	//		m_enemyDeathSound.play();
	//		m_enemies.m_enemiesArray.at(i).setPosition(2000, 2000);
	//		bulletCollided = true;
	//		m_enemies.firstenemyDestroyed = true;
	//		m_enemies.delayedSpawn++;
	//		
	//		bulletLeft = false;
	//	}
	//
	//}
	if (bulletCollided == true)
	{
		enemiesShot++;
		bulletLeft = true;
		bulletCollided = false;
	}
	
	
	
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
			//m_tank.tankBullet.readyTofire = true;
			shotsFired++;
			break;
		
		default:
			break;
		}
	}
}
// used to make the walls
void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_texture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);
	}

	
}

void Game::accuracyCalc()
{
	if(gamefinished==true&&shotsFired>0)
	{
 		totalAcuracy =(enemiesShot /shotsFired )*(100);
	}
	accuracyText.setString("player accuracy "+std::to_string(totalAcuracy)+ "%");
	ScoreText.setString("SCORE : " + std::to_string(enemiesShot));
	tank_fuel_text.setString("player fuel : " + std::to_string(m_tank.m_tankFuel)+"fuel Leak =" +std::to_string(m_fuelLeak));
}

void Game::setupLine()
{
	m_directionTriangle.setRotation(m_tank.m_rotation);
	
	m_tankLineStart.position.x = m_window.getSize().x / 2;
	m_tankLineStart.position.y = m_window.getSize().y / 2;
	m_tankLineEnd.position.x = m_tank.getTankBase().getPosition().x;
	m_tankLineEnd.position.y = m_tank.getTankBase().getPosition().y;

	m_tankLineEnd.color = sf::Color::Red;
	m_tankLineStart.color = sf::Color::Red;
	if (lineDrawn == false)
	{
		m_tankLine.append(m_tankLineEnd);
		m_tankLine.append(m_tankLineStart);
		lineDrawn = true;
	}
	
	
}






////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	collsionDectection();
	accuracyCalc();
	switch (m_gameState)
	{
	default:
	case GameState::GAME_RUNNING:
		std::cout << "GAME::RUNNING" << std::endl;
		if (m_tank.m_tankFuel > 0)
		{
			m_tank.update(dt, m_level.m_tank.m_postion, m_level.m_tank.rotation, m_funcApplyDamage, m_aiTankOne.getTankBase());
			m_tank.m_pool.update(dt, m_wallSprites, m_funcApplyDamage, m_aiTankOne.getTankBase());
		}
		
		m_aiTankOne.seek(m_tank.getPosition());
		m_aiTankOne.update(m_tank, dt);
	//	m_enemies.update(dt, clock, m_level.m_enemies.at(0).m_position, m_level.m_enemies.at(1).m_position, m_level.m_enemies.at(2).m_position, m_level.m_enemies.at(3).m_position);
		break;
	case GameState::GAME_LOSE:
		std::cout << "GAME::LOSE" << std::endl;
		break;
	case GameState::GAME_WIN:
		std::cout << "GAME::WIN" << std::endl;
		break;

	}
	if (m_prize.getGlobalBounds().intersects(m_tank.getTankBase().getGlobalBounds()))
	{
		m_prize.setPosition(m_tank.getTankBase().getPosition());
	}
	if (m_prize.getGlobalBounds().intersects(goalLocation.getGlobalBounds()))
	{
		goalAchieved = true;
	}
	if (m_aiTankOne.m_AiTankHealth <= 0)
	{
		m_gameState=GameState::GAME_WIN;
		std::cout << "tank destroyed" << std::endl;
	}
	if (m_aireleaseTank == false)
	{
		if (m_aiTankOne.collidesWithPlayer(m_tank) == true)
		{
			m_gameState = GameState::GAME_LOSE;
			m_gameDelay+=dt;
			m_tank.m_tankFuel = m_tank.m_tankFuel  - m_fuelLeak;
			if (m_gameDelay == 1050)
			{

				clock.restart();
				m_gameState = GameState::GAME_RUNNING;
				m_aireleaseTank = true;

			}
		}

	}
	
	
	if (m_tank.offScreen() == true)
	{
		
		setupLine();
	}
	else
	{
		lineDrawn = false;
	}
	m_hud.update(GameState::GAME_RUNNING);
	
	if (m_fuel.getGlobalBounds().intersects(m_tank.getTankBase().getGlobalBounds()))
	{
		m_fuel.setPosition(2000, 2000);
		m_tank.m_tankFuel += 2000;
		
	}
	
	//m_tank.tankBullet.update(dt, m_level.m_tank.m_postion,m_level.m_tank.rotation,m_tank.m_rotation);
	

	timerCut = clock.getElapsedTime().asSeconds();
	clockTextTimer.setString("time :" + std::to_string(timerCut));
	if (enemiesShot > 0)
	{
		gamefinished = true;
	}
	
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	// Render your sprites here....
	if (clock.getElapsedTime().asSeconds() <= 30)
	{

		m_window.draw(m_BackGroundSprite);
	
	//	m_tank.tankBullet.render(m_window);
		m_aiTankOne.render(m_window);
		m_tank.render(m_window);
		m_window.draw(clockTextTimer);
		m_window.draw(ScoreText);
		//m_enemies.render(m_window);
		if (m_tank.offScreen() == true)
		{
			m_window.draw(m_tankLine);
			m_window.draw(m_directionTriangle);
			
		}
		else
		{
			m_tankLine.clear();
		}
		
		m_window.draw(tank_fuel_text);
		m_window.draw(goalLocation);
		m_window.draw(m_prize);
		m_window.draw(m_fuel);
		
		for (sf::Sprite wall : m_wallSprites)
		{
			m_window.draw(wall);
		}
	}


	


    if(timerCut==30 || m_tank.m_tankFuel == 0)
	{
		m_window.clear();
		
		m_window.draw(accuracyText);
		m_window.draw(gameOver);
		
	}
	if (enemiesShot >= 4||goalAchieved==true)
	{
		m_window.clear();
	
		m_window.draw(accuracyText);
		m_window.draw(gameWin);
	}
	

	m_window.display();
}





