#include "Game.h"


//author : donal howe

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game() : m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default), m_tank(m_texture, m_wallSprites),
m_enemies(m_wallSprites), m_aiTankOne(m_texture, m_wallSprites)
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


	if (!font.loadFromFile("./resources/images/BebasNeue.otf"))
	{
		std::cout << "not loading" << std::endl;
		//}
	}
	if (!m_enemyDeathSoundABuffer.loadFromFile("./resources/images/enemyDeath.wav"))
	{
		std::cout << "error loading sound" << std::endl;
	}
	m_enemyDeathSound.setBuffer(m_enemyDeathSoundABuffer);


	clockTextTimer.setFont(font);

	clockTextTimer.setPosition(100, 50);
	clockTextTimer.setFillColor(sf::Color::White);
	clockTextTimer.setCharacterSize(30);

	ScoreText.setFont(font);

	ScoreText.setPosition(100, 80);
	ScoreText.setFillColor(sf::Color::Red);
	ScoreText.setCharacterSize(30);

	accuracyText.setFont(font);

	accuracyText.setPosition(500, 300);
	accuracyText.setFillColor(sf::Color::White);
	accuracyText.setCharacterSize(30);

	//setting up the tank line
	

	gameOver.setFont(font);
	gameOver.setString("Gameover out of time");
	gameOver.setPosition(500, 500);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setCharacterSize(30);

	gameWin.setFont(font);
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
	for (int i = 0; i < m_enemies.MAX_ENEMIES; i++)
	{
		if (m_tank.tankBullet.bulletSprite.getGlobalBounds().intersects(m_enemies.m_enemiesArray.at(i).getGlobalBounds()))
		{
			m_enemyDeathSound.play();
			m_enemies.m_enemiesArray.at(i).setPosition(2000, 2000);
			bulletCollided = true;
			m_enemies.firstenemyDestroyed = true;
			m_enemies.delayedSpawn++;
			
			bulletLeft = false;
		}
	
	}
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
			m_tank.tankBullet.readyTofire = true;
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
}

void Game::setupLine()
{
	m_directionTriangle.setRotation(m_tank.m_rotation);
	
	m_tankLineStart.position.x = m_window.getSize().x / 2;
	m_tankLineStart.position.y = m_window.getSize().y / 2;
	m_tankLineEnd.position.x = m_tank.m_tankBase.getPosition().x;
	m_tankLineEnd.position.y = m_tank.m_tankBase.getPosition().y;

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
	if (m_tank.offScreen() == true)
	{
		
		setupLine();
	}
	else
	{
		lineDrawn = false;
	}
	
	
	m_tank.update(dt,m_level.m_tank.m_postion, m_level.m_tank.rotation);
	
	m_enemies.update(dt, clock, m_level.m_enemies.at(0).m_position, m_level.m_enemies.at(1).m_position, m_level.m_enemies.at(2).m_position, m_level.m_enemies.at(3).m_position);
	m_aiTankOne.seek(m_tank.getPosition());
	m_aiTankOne.update(m_tank,dt);
	m_tank.tankBullet.update(dt, m_level.m_tank.m_postion,m_level.m_tank.rotation,m_tank.m_rotation);
	m_tank.bulletParticle.update(dt ,m_level.m_tank.m_postion, clock);

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
		m_tank.bulletParticle.render(m_window);
		m_tank.tankBullet.render(m_window);
		m_aiTankOne.render(m_window);
		m_tank.render(m_window);
		m_window.draw(clockTextTimer);
		m_window.draw(ScoreText);
		m_enemies.render(m_window);
		if (m_tank.offScreen() == true)
		{
			m_window.draw(m_tankLine);
			m_window.draw(m_directionTriangle);
			
		}
		else
		{
			m_tankLine.clear();
		}
		
		for (sf::Sprite wall : m_wallSprites)
		{
			m_window.draw(wall);
		}
	}


	


    if(timerCut==30)
	{
		m_window.clear();
		
		m_window.draw(accuracyText);
		m_window.draw(gameOver);
		
	}
	if (enemiesShot >= 4)
	{
		m_window.clear();
	
		m_window.draw(accuracyText);
		m_window.draw(gameWin);
	}
	

	m_window.display();
}





