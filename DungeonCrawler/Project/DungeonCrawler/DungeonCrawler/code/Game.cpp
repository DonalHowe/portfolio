#include "Game.h"
#include "LevelLoader.h"



// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;




Game::Game() : m_window(sf::VideoMode(ScreenSize::screen_width,ScreenSize::screen_height , 32), "Best Dungeon Crawler", sf::Style::Default),m_menu(m_babaFont)
{
	m_window.setVerticalSyncEnabled(true);
	m_menu.musicInitiliser();
	musicInitiliser();
	if (!m_babaFont.loadFromFile("rescources/images/USED-IMAGES/BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	

	levelNum = 1;


	srand(time(NULL));

	if (levelNum == 1)
	{
		m_menu.m_gstates = GameStates::Menu;
	}
	else if (levelNum == 2)
	{
		m_menu.m_gstates = GameStates::LevelTwo;
	}
	else if (levelNum == 3)
	{
		m_menu.m_gstates = GameStates::LevelThree;
	}
	else if (levelNum == 4)
	{
		m_menu.m_gstates = GameStates::LevelFour;
	}


	loadLevel(levelNum);
	
	
	setUpSprites();
	myKey.setupSprite(m_keyTexture, m_level.m_key.position, m_level.m_key.size);
	playerOne.GetSword()->setupSword(m_level.m_sword.m_fileName);
	myInventory.setupSprites(m_level.m_key.m_fileName,m_level.m_sword.m_fileName,m_level.m_axe.m_fileName);
	playerOne.GetAxe()->setupAxe(m_level.m_axe.m_fileName,m_level.m_axe.size);
	myGrid.setUpCellIDNumText(m_babaFont);
	for (int i = 0; i < golemEneny.GetMaxGolems(); i++)
	{
		walkerVector.push_back(golemEneny);
	}
	
	Node* startNode;
	Node* endnode;
	startNode = myGrid.atIndex(10);
	endnode = myGrid.atIndex(8);

	myGrid.m_gridStack=myGrid.aStar(startNode, endnode, myGrid.aStarPath,levelNum);
	
	int i = 0;
	while (endnode != nullptr)
	{
		int x = endnode->GetId() % myGrid.m_MAX_ROWS;
		int y = endnode->GetId() / myGrid.m_MAX_ROWS;
		//std::cout << "path " << endnode->GetId() <<" & X: " << x << " Y: " << y << std::endl;


		myGrid.m_GridVec.at(x).at(y).m_rect.setFillColor(sf::Color::Yellow);
		endnode = endnode->GetPrevious();

	}



	
	
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

void Game::setUpSprites()
{
	
	startLevelDoor.setPosition(m_level.m_door.position);
	startLevelDoor.setFillColor(sf::Color::Transparent);
	startLevelDoor.setSize(m_level.m_door.size);
	if (!torchTexture.loadFromFile("rescources/images/USED-IMAGES/TORCH4.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	if (!puddleTexture.loadFromFile("rescources/images/USED-IMAGES/puddle1.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	if (!circleTexture.loadFromFile("rescources/images/USED-IMAGES/circle.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}



	for (int i = 0; i < m_level.m_torches.size(); i++)
	{
		sf::Sprite tempTorch;
		tempTorch.setTexture(torchTexture);
		tempTorch.setPosition(m_level.m_torches.at(i).position);
		torchSpriteVec.push_back(tempTorch);

		torchSpriteVec.at(i).setScale(m_level.m_torches.at(i).xScale,
			m_level.m_torches.at(i).yScale);

	}
	for (int i = 0; i < 3; i++)
	{
		cageTop[i].setFillColor(sf::Color::Red);
	}

	cageTop[0].setSize(sf::Vector2f(275, 10));
	cageTop[1].setSize(sf::Vector2f(275, 10));
	cageTop[2].setSize(sf::Vector2f(10, 190));

	cageTop[0].setPosition(110, 350);
	cageTop[1].setPosition(110, 170);
	cageTop[2].setPosition(120, 170);

	for (int i = 0; i < 4; i++)
	{
		columnSquare[i].setFillColor(sf::Color::Transparent);
	}
	columnSquare[0].setSize(sf::Vector2f(100, 135));
	columnSquare[1].setSize(sf::Vector2f(100, 135));
	columnSquare[2].setSize(sf::Vector2f(100, 135));
	columnSquare[3].setSize(sf::Vector2f(100, 135));


	columnSquare[0].setPosition(240, 510);
	columnSquare[1].setPosition(240, 175);
	columnSquare[2].setPosition(668, 510);
	columnSquare[3].setPosition(668, 175);

	levelOneInfo.setFont(m_babaFont);
	levelOneInfo.setPosition(200, 20);
	levelOneInfo.setString("Find the key !");

	levelTwoInfo.setFont(m_babaFont);
	levelTwoInfo.setPosition(200, 20);
	levelTwoInfo.setString("Kill all enemies !");

	levelThreeInfo.setFont(m_babaFont);
	levelThreeInfo.setPosition(200, 20);
	levelThreeInfo.setString("Find the way out !");

	mazeExit.setRadius(50.0f);
	mazeExit.setOrigin(25.0f,25.0f);
	mazeExit.setPosition(850, 15);
	mazeExit.setFillColor(sf::Color::Green);

	puddleOneSprite[0].setTexture(puddleTexture);
	puddleOneSprite[1].setTexture(puddleTexture);

	puddleOneSprite[0].setScale(0.3, 0.3);
	puddleOneSprite[1].setScale(0.3, 0.3);

	puddleOneSprite[0].setPosition(100, 450);
	puddleOneSprite[1].setPosition(700, 450);

	wipeAttackBar.setFillColor(sf::Color::Red);
	wipeAttackBar.setSize(sf::Vector2f(25.0f, -gameTimer));
	wipeAttackBar.setPosition(60, 870);


	wipeAttackBarOutlineFixed.setFillColor(sf::Color::Transparent);
	wipeAttackBarOutlineFixed.setOutlineColor(sf::Color::Black);
	wipeAttackBarOutlineFixed.setOutlineThickness(10);
	wipeAttackBarOutlineFixed.setSize(sf::Vector2f(25.0f, -700));
	wipeAttackBarOutlineFixed.setPosition(60, 870);

	circleSprite.setTexture(circleTexture);
	circleSprite.setScale(0.00001f,0.00001f);
	circleSprite.setOrigin(945, 945);
	circleSprite.setColor(sf::Color::Transparent);
}

void Game::musicInitiliser()
{
	if (!m_axeSoundsBuffer.loadFromFile("rescources/sound/axeSound.ogg"))
	{
		std::cout << "cant load song file" << std::endl;
	}
	m_axeSounds.setBuffer(m_axeSoundsBuffer);

	if (!m_dragonFireSoundBuffer.loadFromFile("rescources/sound/dragsound.ogg"))
	{
		std::cout << "cant load song file" << std::endl;
	}
	m_dragonFireSound.setBuffer(m_dragonFireSoundBuffer);
	

}




////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& t_event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == t_event.type)
	{
		switch (t_event.key.code)
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



void Game::loadLevel(int t_levelId)
{
	invisWallVec.clear();
	m_level.m_invisWallBounds.clear();
	// Will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(t_levelId, m_level);
		
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
	{
		
		m_tempRect.setSize(m_level.m_invisWallBounds.at(i).size);
		m_tempRect.setFillColor(sf::Color::Transparent);
		invisWallVec.push_back(m_tempRect);
	}

	for (int i = 0; i < m_level.m_mazeWallVec.size(); i++)
	{

		m_tempRect.setSize(m_level.m_mazeWallVec.at(i).size);
		m_tempRect.setPosition(m_level.m_mazeWallVec.at(i).position);
		m_tempRect.setFillColor(sf::Color::Black);
		mazeWalls.push_back(m_tempRect);
	}


	if (!roomOneTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::cout << "cant load sprite" << std::endl;

	}
	if (!roomOneCageTexture.loadFromFile(m_level.m_cage.m_fileName))
	{
		std::cout << "cant load sprite cage" << std::endl;

	}
	if (t_levelId == 1)
	{
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			invisWallVec.at(i).setPosition(m_level.m_invisWallBounds.at(i).position);
		}
		
	}
	else if (t_levelId == 2)
	{

		roomOneBackgroundSp.setScale(1.65, 1.3);
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			invisWallVec.at(i).setPosition(m_level.m_invisWallBounds.at(i).position);
			
		}
	
			playerOne.GetAxe()->m_sprite.setPosition(m_level.m_axe.position);
			playerOne.GetSword()->m_sprite.setPosition(m_level.m_sword.position);

	}
	else if (t_levelId == 3)
	{
		roomOneBackgroundSp.setScale(2.0f, 2.0f);
		roomOneBackgroundSp.setPosition(-200,-200);
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			invisWallVec.at(i).setPosition(m_level.m_invisWallBounds.at(i).position);

		}
		for (int i = 0; i < m_level.m_mazeWallVec.size(); i++)
		{

			m_tempRect.setSize(m_level.m_mazeWallVec.at(i).size);
			m_tempRect.setPosition(m_level.m_mazeWallVec.at(i).position);
			m_tempRect.setFillColor(sf::Color::Black);
			mazeWalls.push_back(m_tempRect);
		}
	}
	else if (t_levelId == 4)
	{
		roomOneBackgroundSp.setScale(1.25f, 2.0f);
		roomOneBackgroundSp.setPosition(0, 0);
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			invisWallVec.at(i).setPosition(m_level.m_invisWallBounds.at(i).position);

		}
	}


	roomOneBackgroundSp.setTexture(roomOneTexture);
	roomOneCageSprite.setTexture(roomOneCageTexture);
	roomOneCageSprite.setPosition(430, 150);
	roomOneCageSprite.setRotation(90);

	
	
	

	if (!m_keyTexture.loadFromFile(m_level.m_key.m_fileName))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	
	hasLevelLoaded = true;
	
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		Node* startNode;
		Node* endnode;
		startNode = myGrid.atIndex(20);
		endnode = myGrid.atIndex(83);
		if (aStarRun == false)
		{
			while (myGrid.m_gridStack.size()!=0)
			{
				myGrid.m_gridStack.pop();
			}
			myGrid.aStar(startNode, endnode, myGrid.aStarPath,levelNum);
			

		}
		aStarRun = true;
		while (endnode != nullptr)
		{
			int x = endnode->GetId() % myGrid.m_MAX_ROWS;
			int y = endnode->GetId() / myGrid.m_MAX_ROWS;
			//std::cout << "path " << endnode->GetId() <<" & X: " << x << " Y: " << y << std::endl;


			myGrid.m_GridVec.at(x).at(y).m_rect.setFillColor(sf::Color::Yellow);
			endnode = endnode->GetPrevious();

		}

		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		levelNum++ ;
		if (hasLevelLoaded == false)
		{
			loadLevel(levelNum);
		}
		
	}

	
	if (m_menu.m_gstates== GameStates::Menu)
	{
		m_menu.update(dt);
		
		
	}
	if (m_menu.m_gstates != GameStates::Menu)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			view2 = sf::View(sf::Vector2f(playerOne.GetSprite().getPosition().x , playerOne.GetSprite().getPosition().y), sf::Vector2f(500.f, 500.f));
		}

	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_menu.m_menuSwitcher = MenuStates::Inventory;
		view2 = sf::View(sf::Vector2f(ScreenSize::screen_width/2, ScreenSize::screen_height/2), sf::Vector2f(ScreenSize::screen_width, ScreenSize::screen_height));
	}

	if (playerOne.playerHp > 0)
	{
		if (levelNum == 1 && m_menu.m_gstates == GameStates::LevelOne) //1st level
		{
			myKey.update(dt);
			levelOneInfo.setPosition(playerOne.m_playerSprite.getPosition().x - 240, playerOne.m_playerSprite.getPosition().y - 250);
			playerOne.update(dt);
			animateSprite();

			collisions();
			dummyEnemy.update(dt);
			if (playerOne.collisionWithEnemy(dummyEnemy.dumbEnemySprite) == true)
			{
				playerOne.SetSpritePos(playerOne.GetStartPos());

			}

			if (myInventory.GetGotKeyBoolean() == false)
			{

				playerOne.collisionWithKey(myKey.m_Sprite);


				if (playerOne.collisionWithKey(myKey.m_Sprite) == true)
				{
					collectedKey = true;
					myInventory.collectedItems(collectedKey, collectedSword, collectedAxe);
				}

			}
			myGrid.update(dt);


		}
		else if (levelNum == 2 && m_menu.m_gstates == GameStates::LevelTwo)
		{
			levelTwoInfo.setPosition(playerOne.m_playerSprite.getPosition().x - 240, playerOne.m_playerSprite.getPosition().y - 250);

			playerOne.collisionWithKey(myKey.m_Sprite);
			playerOne.update(dt);
			playerOne.GetSword()->update(dt);
			playerOne.GetAxe()->update(dt);
			animateSprite();
			collisions();
			selectWeapons();
			particlesSystem.Update();
			particles.Update();

			for (int i = 0; i < golemEneny.GetMaxGolems(); i++)
			{
				walkerVector.at(i).update(dt);
			}
			if (playerOne.collisionWithSword(playerOne.GetSword()->m_sprite) == true)
			{
				collectedSword = true;
				myInventory.collectedItems(collectedKey, collectedSword, collectedAxe);
			}

			if (playerOne.collisionWithSword(playerOne.GetAxe()->m_sprite) == true)
			{
				collectedAxe = true;

				myInventory.collectedItems(collectedKey, collectedSword, collectedAxe);
			}
			if (collectedAxe)
			{
				if (playerOne.GetPlayerDirection() == 1)
				{
					playerOne.GetAxe()->m_sprite.setPosition(playerOne.GetSprite().getPosition().x, playerOne.GetSprite().getPosition().y - 40);
					playerOne.GetAxe()->m_sprite.setScale(0.2, 0.2);
					playerOne.GetAxe()->m_sprite.setRotation(0);


				}
				if (playerOne.GetPlayerDirection() == 2)
				{
					playerOne.GetAxe()->m_sprite.setPosition(playerOne.GetSprite().getPosition().x, playerOne.GetSprite().getPosition().y - 40);
					playerOne.GetAxe()->m_sprite.setScale(-0.2, 0.2);
					playerOne.GetAxe()->m_sprite.setRotation(0);

				}

				if (playerOne.GetPlayerDirection() == 3)
				{
					playerOne.GetAxe()->m_sprite.setPosition(playerOne.GetSprite().getPosition().x - 40, playerOne.GetSprite().getPosition().y);
					playerOne.GetAxe()->m_sprite.setScale(0.18, 0.18);
					playerOne.GetAxe()->m_sprite.setRotation(270);
				}
				if (playerOne.GetPlayerDirection() == 4)
				{
					playerOne.GetAxe()->m_sprite.setPosition(playerOne.GetSprite().getPosition().x + 40, playerOne.GetSprite().getPosition().y - 5);
					playerOne.GetAxe()->m_sprite.setScale(0.2, 0.2);
					playerOne.GetAxe()->m_sprite.setRotation(90);
				}

			}
			if (m_WeaponSwitcher == WeaponSelection::sword)
			{
				//this is maybe to attack a enemy

			}
			else if (m_WeaponSwitcher == WeaponSelection::Axe)
			{
				// this is maybe to attack a enemy

			}
			if (levelTwoEnemyLives >= 5)
			{
				levelNum = 3;
				loadLevel(levelNum);
				m_menu.m_gstates = GameStates::LevelThree;
			}

		}

		else if (levelNum == 3 && m_menu.m_gstates == GameStates::LevelThree)
		{
			levelThreeInfo.setPosition(playerOne.m_playerSprite.getPosition().x - 240, playerOne.m_playerSprite.getPosition().y - 250);

			playerOne.update(dt);
			animateSprite();
			collisions();
			myGrid.update(dt);
			m_mazeGuide.update(dt);
			playerOne.m_playerSprite.setScale(0.6, 0.6);
			levelEditorMaze();
			if (levelCheckForLvl3 == 1)
			{
				playerOne.m_playerSprite.setPosition(127, 123);
				levelCheckForLvl3++;
			}
			circleSprite.setPosition(sf::Vector2f(m_mousePos));
			checkForFairy++;

			if (checkForFairy > 500)
			{
				if (myGrid.m_gridStack.size() != 0) {

					if (m_mazeGuide.m_shape.getPosition() == myGrid.m_gridStack.top()->getPosition())
					{

						myGrid.m_gridStack.pop();
					}
					else
					{
						m_mazeGuide.movement(myGrid.m_gridStack.top()->getPosition());

					}
				}
			}
			if (m_menu.getEditor()==true)
			{
				levelEditor = true;
			}

		}

		else if (levelNum == 4 && m_menu.m_gstates == GameStates::LevelFour)
		{
			bossPathfindAttack();

			if (levelCheckForLvl4 == 1)
			{
				playerOne.m_playerSprite.setPosition(500, 800);
				levelCheckForLvl4++;
			}

			playerOne.update(dt);
			playerOne.shootFireBall();
			boss.update(dt);
			boss.movement(ScreenSize::screen_width, ScreenSize::screen_height);
			playerOne.screenBoundForLevelThree(ScreenSize::screen_width, ScreenSize::screen_height);
			boosAttack();
			collisions();
			particlesSystem.Update();
			particlesSystemBoss.Update();
			myGrid.update(dt);

			if (gameTimer < 700)
			{
				wipeAttackBar.setSize(sf::Vector2f(25.0f, -gameTimer));
			}

			std::cout << " THIS IS X:  " << m_mousePos.x << " THIS IS Y:  " << m_mousePos.y << std::endl;

			if (myGrid.m_gridStack.size() != 0) {

				if (boss.wipeBallBossSprite.getPosition() == myGrid.m_gridStack.top()->getPosition())
				{
					myGrid.m_gridStack.pop();
				}
				else
				{
					boss.wipeBallMovement(myGrid.m_gridStack.top()->getPosition());
				}
			}

		}


	}

	if (playerOne.playerHp <= 0)
	{

		levelThreeInfo.setScale(3,3);
		levelThreeInfo.setOrigin(levelThreeInfo.getGlobalBounds().width /2 , levelThreeInfo.getGlobalBounds().height / 2);
		levelThreeInfo.setString("GAME OVER");

		levelThreeInfo.setPosition(800, ScreenSize::screen_height / 2);
	}

	if (boss.m_bossHP <= 0)
	{
		levelThreeInfo.setScale(3, 3);
		levelThreeInfo.setOrigin(levelThreeInfo.getGlobalBounds().width / 2, levelThreeInfo.getGlobalBounds().height / 2);
		levelThreeInfo.setString("YOU WIN !!!");
		levelThreeInfo.setPosition(800, ScreenSize::screen_height / 2);
	}

	
}


////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_mousePos = sf::Mouse::getPosition(m_window);

	if (m_menu.m_gstates == GameStates::Menu)
	{
		m_menu.render(m_window);
	
	}
	else  
	{
		//playerOne.render(m_window);
		
		if (levelNum == 1)
		{
			m_window.draw(roomOneBackgroundSp);
			playerOne.render(m_window);
			m_window.draw(startLevelDoor);
			m_window.draw(levelOneInfo);
			if (myInventory.GetGotKeyBoolean() == false)
			{
				myKey.render(m_window);

			}
			for (int i = 0; i < 3; i++)
			{
				m_window.draw(cageTop[i]);
			}
			dummyEnemy.render(m_window);
			for (int i = 0; i < torchSpriteVec.size(); i++)
			{
				m_window.draw(torchSpriteVec.at(i));
			}
			m_window.draw(roomOneCageSprite);
			for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
			{
				m_window.draw(invisWallVec.at(i));

			}

		}
		else if (levelNum == 2)
		{
			m_window.draw(roomOneBackgroundSp);
			for (int i = 0; i < golemEneny.GetMaxGolems(); i++)
			{
				walkerVector.at(i).render(m_window);

			}
			//golemEneny.render(m_window);

			for (int i = 0; i < 4; i++)
			{
				m_window.draw(columnSquare[i]);
			}
			if (collectedSword == false)
			{
				m_window.draw(playerOne.GetSword()->m_sprite);
			}

			playerOne.render(m_window);

			m_window.draw(playerOne.GetAxe()->m_sprite);
			particlesSystem.Draw(m_window);
			particles.Draw(m_window);
			m_window.draw(levelTwoInfo);
		
		}
		else if(levelNum == 3)
		{
			m_window.draw(roomOneBackgroundSp);
			m_window.draw(playerOne.GetSprite());
			m_window.draw(levelThreeInfo);
			m_window.draw(mazeExit);
			m_window.draw(circleSprite);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				myGrid.render(m_window);
				view2 = sf::View(sf::Vector2f(ScreenSize::screen_width / 2, ScreenSize::screen_height / 2), sf::Vector2f(ScreenSize::screen_width, ScreenSize::screen_height));
			}


			if (levelEditor)
			{
				view2 = sf::View(sf::Vector2f(ScreenSize::screen_width / 2, ScreenSize::screen_height / 2), sf::Vector2f(ScreenSize::screen_width, ScreenSize::screen_height));

			}
			else {

			}
			for (int i = 0; i < 50; i++)
			{
				m_window.draw(mazeWalls.at(i));
			}
			

			m_mazeGuide.render(m_window);
		}
		else if (levelNum == 4)
		{
			m_window.draw(roomOneBackgroundSp);
			m_window.draw(puddleOneSprite[0]);
			m_window.draw(puddleOneSprite[1]);
			playerOne.m_playerSprite.setScale(1,1);
			boss.render(m_window);
			view2 = sf::View(sf::Vector2f(ScreenSize::screen_width / 2, ScreenSize::screen_height / 2), sf::Vector2f(ScreenSize::screen_width, ScreenSize::screen_height));
			m_window.draw(playerOne.GetSprite());
			playerOne.render(m_window);
			particlesSystem.Draw(m_window);
			particles.Draw(m_window);
			particlesSystemBoss.Draw(m_window);
			m_window.draw(wipeAttackBarOutlineFixed);
			m_window.draw(wipeAttackBar);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			myGrid.render(m_window);
		}
	

	


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			myInventory.render(m_window);
		}
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			m_window.draw(invisWallVec.at(i));

		}


		if (playerOne.playerHp <= 0 || boss.m_bossHP <= 0)
		{
			m_window.draw(levelThreeInfo);
		}
	}

	

	// create a view with its center and size
	m_window.setView(view2);

	
	
	m_window.display();
};


void Game::animateSprite()
{
	for (int i = 0; i < torchSpriteVec.size(); i++)
	{
		m_playerFrameCounter += m_playerFrameIncrement;
		m_playerFrame = static_cast<int>(m_playerFrameCounter) % 6; // change valuues later to see the difference 
		torchSpriteVec.at(i).setTextureRect(sf::IntRect{ m_playerFrame * 35, 0, 33 , 100 });
	}
	




}
void Game::collisions()
{
	// pretty certain this is where the problem is for why the level transitions back into the previous one 
	if (collectedKey == true)
	{
		if (playerOne.GetSprite().getGlobalBounds().intersects(startLevelDoor.getGlobalBounds()))
		{

			if (levelNum == 1)
			{
				levelNum = 2;
				loadLevel(levelNum);
				m_menu.m_gstates = GameStates::LevelTwo;
			}
		}
	}

	if (levelNum == 3)
	{
		if (playerOne.GetSprite().getGlobalBounds().intersects(mazeExit.getGlobalBounds()))
		{

			levelNum = 4;
			loadLevel(levelNum);
			m_menu.m_gstates = GameStates::LevelFour;

		}
	}


	//collision with cage
	if (levelNum == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (playerOne.GetSprite().getGlobalBounds().intersects(cageTop[i].getGlobalBounds()))
			{
				playerOne.deflect();
				//playerOne.playerHp = playerOne.playerHp - 10.0f;

			}
		}
	}
	if (levelNum == 3)
	{
		for (int i = 0; i < 50; i++)
		{
			if (playerOne.GetSprite().getGlobalBounds().intersects(mazeWalls[i].getGlobalBounds()))
			{
				playerOne.deflect();
			}
		}
	}


	// collisions for player/golems with collumns
	if (levelNum == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < golemEneny.GetMaxGolems(); j++)
			{
				if (walkerVector.at(j).GetSprite().getGlobalBounds().intersects(columnSquare[i].getGlobalBounds()))
				{
					walkerVector.at(j).deflect();

				}
				if (walkerVector.at(j).GetSprite().getGlobalBounds().intersects(invisWallVec.at(i).getGlobalBounds()))
				{
					walkerVector.at(j).deflect();
				}
			}
		}




		for (int i = 0; i < walkerVector.size(); i++)
		{
			if (playerOne.GetSprite().getGlobalBounds().intersects(columnSquare[i].getGlobalBounds()))
			{
				playerOne.deflect();
			}



			if (collectedAxe == true)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					sf::Vector2f tempPos = walkerVector.at(i).tempSprite.getPosition();
					if (playerOne.collisionWithGolem(walkerVector.at(i).tempSprite) == true) {
						particlesSystem.Initialise(sf::Vector2f{ tempPos.x + 50,tempPos.y + 30 });

						walkerVector.at(i).bloodStainSprite.setPosition(walkerVector.at(i).GetSprite().getPosition().x, walkerVector.at(i).GetSprite().getPosition().y);
						m_axeSounds.play();
						walkerVector.at(i).tempSprite.setPosition(40000, 40000);
						levelTwoEnemyLives += 1;
					}
				}
			}
			if (collectedSword == true)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (playerOne.collisionWithGolem(walkerVector.at(i).tempSprite) == true) {

						walkerVector.at(i).tempSprite.setPosition(40000, 40000);
						levelTwoEnemyLives += 1;
					}
				}
			}

			for (int j = 0; j < 1; j++)
			{
				if (playerOne.GetSprite().getGlobalBounds().intersects(walkerVector.at(i).rockSprite[j].getGlobalBounds()))
				{
					walkerVector.at(i).rockSprite[j].setPosition(40000, 40000);
					if (walkerVector.at(i).getRockMoving() == true)
					{
						playerOne.playerHp = playerOne.playerHp - 10.0f;
					}
					
				}
			}
		}
	}
	else if (levelNum == 3)
	{
		for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
		{
			if (playerOne.GetSprite().getGlobalBounds().intersects(invisWallVec.at(i).getGlobalBounds()))
			{
				playerOne.deflect();
			}
		}
	}

	else if (levelNum == 4)
	{
		if (playerOne.GetSprite().getGlobalBounds().intersects(boss.fireBallBossSprite.getGlobalBounds()))
		{
			playerOne.playerHp = playerOne.playerHp - 34.0f;
			boss.fireBallBossSprite.setPosition(343434, 3434343);
			std::cout << "COLLIDED" << std::endl;
			sf::Vector2f tempPos = playerOne.GetSprite().getPosition();

			particlesSystem.Initialise(sf::Vector2f{ tempPos.x,tempPos.y });

		}

		if (playerOne.GetSprite().getGlobalBounds().intersects(boss.wipeBallBossSprite.getGlobalBounds()) && boss.wipeBallBossSprite.getColor() == sf::Color::Red)
		{
			playerOne.playerHp = playerOne.playerHp - 100.0f;
			boss.wipeBallBossSprite.setPosition(343434, 3434343);
			std::cout << "COLLIDED" << std::endl;
			sf::Vector2f tempPos = playerOne.GetSprite().getPosition();

			particlesSystem.Initialise(sf::Vector2f{ tempPos.x,tempPos.y });

		}

		if (playerOne.GetSprite().getGlobalBounds().intersects(boss.wipeBallBossSprite.getGlobalBounds()) && boss.wipeBallBossSprite.getColor() == sf::Color::Blue)
		{
			playerOne.playerHp = playerOne.playerHp - 50.0f;
			boss.wipeBallBossSprite.setPosition(343434, 3434343);
			std::cout << "COLLIDED" << std::endl;
			sf::Vector2f tempPos = playerOne.GetSprite().getPosition();

			particlesSystem.Initialise(sf::Vector2f{ tempPos.x,tempPos.y });

		}


		if (playerOne.fireBall.getGlobalBounds().intersects(boss.bossSprite.getGlobalBounds()))
		{
			//playerOne.playerHp = playerOne.playerHp - 50.0f;
			sf::Vector2f tempPos = boss.bossSprite.getPosition();
			std::cout << "COLLIDED WITH BOSS" << std::endl;
			playerOne.fireBall.setPosition(343434, -3434343);
			boss.m_bossHP = boss.m_bossHP - 25;
			particlesSystemBoss.Initialise(sf::Vector2f{ tempPos.x,tempPos.y });

		}

		if (boss.wipeBallBossSprite.getColor() == sf::Color::Red)
		{
			for (int i = 0; i < 3; i++)
			{
				if (puddleOneSprite[i].getGlobalBounds().intersects(boss.wipeBallBossSprite.getGlobalBounds()))
				{
					boss.wipeBallBossSprite.setColor(sf::Color::Blue);
				}
			}
		}

	
	}



	/*for (int i = 0; i < m_level.m_invisWallBounds.size(); i++)
	{
		if (playerOne.GetSprite().getGlobalBounds().intersects(invisWallVec.at(i).getGlobalBounds()))
		{
			playerOne.deflect();
		}
	}*/

}

void Game::boosAttack()
{
	if (boss.m_bossHP > 0)
	{
		bossShotRandomNum = rand() % howOftenBossAttacks + 1;
		//std::cout << bossShotRandomNum << std::endl;
		if (bossShotRandomNum == 1 || bossShotRandomNum == 10 || bossShotRandomNum == 20 || bossShotRandomNum == 30 || bossShotRandomNum == 50 || bossShotRandomNum == 60
			|| bossShotRandomNum == 70 || bossShotRandomNum == 80 || bossShotRandomNum == 90)
		{
			if (boss.fireBallBossSprite.getPosition().y > ScreenSize::screen_height)
			{
				boss.fireBallBossSprite.setPosition(boss.bossSprite.getPosition());
				m_dragonFireSound.play();
				float angleShot = atan2(playerOne.m_playerSprite.getPosition().y - boss.fireBallBossSprite.getPosition().y, playerOne.m_playerSprite.getPosition().x - boss.fireBallBossSprite.getPosition().x);
				angleShot2 = angleShot;  //so it goes in a straight line
				//shot = true;
			}
		}


		boss.fireBallBossSprite.move(cos(angleShot2) * 3.0f, 0);
		boss.fireBallBossSprite.move(0, sin(angleShot2) * 3.0f);
	}
}

void Game::bossPathfindAttack()
{
	if (boss.m_bossHP > 0)
	{
		int startNodeOfTower = 11;

		gameTimer++;
		std::cout << gameTimer << std::endl;
		if (gameTimer == 700)//sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			aStarRun = false;
			if (!isTowerSelected)
			{
				randTower = rand() % 10 + 1;
				//randTower = 3;

				std::cout << "rand is: " << randTower << std::endl;
				isTowerSelected = true;
			}


			if (randTower > 5)
			{
				boss.wipeBallBossSprite.setPosition(225, 95);
				startNodeOfTower = 11;
				boss.wipeBallBossSprite.setColor(sf::Color::Red);

			}
			if (randTower <= 5)
			{
				boss.wipeBallBossSprite.setPosition(726, 95);
				startNodeOfTower = 17;
				boss.wipeBallBossSprite.setColor(sf::Color::Red);

			}

			Node* startNode;
			int playerPositionIndex;
			Node* endnode;
			startNode = myGrid.atIndex(startNodeOfTower);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (myGrid.m_GridVec.at(i).at(j).m_rect.getGlobalBounds().contains(playerOne.m_playerSprite.getPosition()))
					{
						playerPositionIndex = myGrid.m_GridVec.at(i).at(j).GetId();

					}
				}

			}
			endnode = myGrid.atIndex(playerPositionIndex);


			if (aStarRun == false)
			{
				while (myGrid.m_gridStack.size() != 0)
				{
					myGrid.m_gridStack.pop();
				}
				myGrid.aStar(startNode, endnode, myGrid.aStarPath, levelNum);

			}
			aStarRun = true;

			while (endnode != nullptr)
			{
				int x = endnode->GetId() % myGrid.m_MAX_ROWS;
				int y = endnode->GetId() / myGrid.m_MAX_ROWS;
				//std::cout << "path " << endnode->GetId() <<" & X: " << x << " Y: " << y << std::endl;
				myGrid.m_GridVec.at(x).at(y).m_rect.setFillColor(sf::Color::Yellow);
				endnode = endnode->GetPrevious();
			}
		}
		if (gameTimer > 1500)
		{
			gameTimer = 0;
		}
	}
}

void Game::selectWeapons()
{
	if (collectedAxe == true)
	{
		playerOne.setcanAttackEnemy(collectedAxe, collectedSword);
	}
	if (collectedSword == true)
	{
		playerOne.setcanAttackEnemy(collectedAxe, collectedSword);
	}

}


void Game::levelEditorMaze()
{
	if (levelEditor)
	{
		for (int i = 0; i < 50; i++)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && circleSprite.getGlobalBounds().intersects(mazeWalls[i].getGlobalBounds()))
			{
				editorBeingUsed = true;
				tempWallPos = i;
				mazeWalls.at(tempWallPos).setPosition(sf::Vector2f(m_mousePos));

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			levelEditor = false;
		}
		//std::cout << "X: " << mazeWalls.at(0).getPosition().x << "Y: " << mazeWalls.at(0).getPosition().y << std::endl;

	}
}


