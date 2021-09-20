#include "..\header\enemybfs.h"

void EnemyBFS::animateSprites()
{
}

void EnemyBFS::initilise()
{
	if (!m_farmerTexture.loadFromFile("resources/img/farmerSpriteSheet.png"))
	{
		std::cout << "Error with farmer main spritesheet file";
	}

	if (!m_farmerUpTexture.loadFromFile("resources/img/farmerSpriteSheet_up.png"))
	{
		std::cout << "Error with farmer up file";
	}

	if (!m_farmerDownTexture.loadFromFile("resources/img/farmerSpriteSheet_down.png"))
	{
		std::cout << "Error with farmer down file";
	}

	if (!m_farmerLeftTexture.loadFromFile("resources/img/farmerSpriteSheet_left.png"))
	{
		std::cout << "Error with farmer left file";
	}

	if (!m_farmerRightTexture.loadFromFile("resources/img/farmerSpriteSheet_right.png"))
	{
		std::cout << "Error with farmer right file";
	}

	m_farmerSprite.setTexture(m_farmerTexture);
	//m_position = theGrid.m_previousCell.at(0).m_Pos;
	//m_farmerSprite.setScale(.5, .5);
	m_position = theGrid.gridVector.at(theGrid.getStartRow()).at(theGrid.getStartCol()).m_Pos;
	m_farmerSprite.setPosition(m_position);
	// so we want the player to move from point ot point eahc cell has a variable called m_pos so from m_pos to m_pos 
}

void EnemyBFS::getPlayerPath()
{
	
	for (int i = 0; i < theGrid.getPath().size(); i++)
	{
		calcRow = theGrid.getPath().at(i) / 10;
		calcCol = theGrid.getPath().at(i) % 10;
		
	}
	m_isMoving = true;
	theGrid.getPath().pop_back();
}

void EnemyBFS::update(double dt)
{
	// state control
	if (farmerStates == FarmerAnimatedStates::walking)
	{
		movement();

		animateSprites();
	}
	if (farmerStates == FarmerAnimatedStates::attack)
	{
		movement();
		animateSprites();
	}
	if (farmerStates == FarmerAnimatedStates::dead)
	{
		
	}
	
}

void EnemyBFS::movement()
{
	// this will be when he follows the path
	// already defined for him by the breadth first search 
	//just have him stagnat for the minute


	
	if (!theGrid.getPath().empty())
	{
		if (m_isMoving == true&&m_reachedDest==false)
		{
			if (m_foundNextPos ==false )
			{
				 currentRow = theGrid.getPath().at(theGrid.getPath().size() - 1) / 10;
				 currentCol = theGrid.getPath().at(theGrid.getPath().size() - 1) % 10;
				//m_position=theGrid.gridVector.at(calcRow).at

				currentPathx = theGrid.gridVector.at(currentRow).at(currentCol).m_Pos.x;
				currentPathy = theGrid.gridVector.at(currentRow).at(currentCol).m_Pos.y;
				currentVelocity = sf::Vector2f(currentPathx, currentPathy) - m_farmerSprite.getPosition();
				currentVelocity = m_speed * thor::unitVector(currentVelocity);
				m_foundNextPos = true;
			}
			
		}
		m_farmerSprite.setPosition(m_farmerSprite.getPosition() + currentVelocity);
		if (thor::length(m_farmerSprite.getPosition()- sf::Vector2f(currentPathx, currentPathy)) <= 1.45f)
		{
			m_foundNextPos = false;
			theGrid.gridVector.at(currentRow).at(currentCol).resetColour();
			theGrid.getPath().pop_back();
		}
	}
	else
	{
		m_isMoving = false;
	}

	
		
	
}

void EnemyBFS::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_farmerSprite);

	animateFarmer(currentFarmerState);
}

EnemyBFS::EnemyBFS()
{
	
	initilise();
	getPlayerPath();
	
}

sf::Sprite EnemyBFS::getFarmer()
{
	return m_farmerSprite;
}

sf::Vector2f EnemyBFS::getPos()
{
	return m_farmerPosition;
}

void EnemyBFS::animateFarmer(FarmerAnimatedStates t_currentFarmerState)
{
	if (t_currentFarmerState == FarmerAnimatedStates::up)
	{
		m_farmerSprite.setTexture(m_farmerUpTexture); // set the correct texture sheet
	}
	else if (t_currentFarmerState == FarmerAnimatedStates::down)
	{
		m_farmerSprite.setTexture(m_farmerDownTexture); // set the correct texture sheet
	}
	else if (t_currentFarmerState == FarmerAnimatedStates::left)
	{
		m_farmerSprite.setTexture(m_farmerLeftTexture); // set the correct texture sheet
	}
	else if (t_currentFarmerState == FarmerAnimatedStates::right)
	{
		m_farmerSprite.setTexture(m_farmerRightTexture); // set the correct texture sheet
	}

	totalElapsed++;

	if (totalElapsed > 16)
	{
		totalElapsed = 0;
		animationFrame++;

		if (animationFrame > 3)
		{
			animationFrame = 0;
		}

	}

	int col = animationFrame % 3; // 3 columns of sprites
	int row = animationFrame / 4; // 4 rows of sprites
	rectSourceSprite.height = 75; // height / width is gotten with the formula :: totalImageWidth / columns = width and  totalImageHeight / rows = height
	rectSourceSprite.width = 60;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_farmerSprite.setTextureRect(rectSourceSprite);
}
