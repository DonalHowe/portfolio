#include "..\header\enemyChickens.h"

enemyChickens::enemyChickens()
{
	loadTextures(); // loads all the textures required for the chicken

	randXPos = rand() % 1200 + 1; // getting the rand positions
	randYPos = rand() % 800 + 1;

	randXHeading = rand() % 1200 + 1;
	randYHeading = rand() % 800 + 1;

	randHeading = {randXHeading, randYHeading};

	sf::Vector2f randSpawn{ randXPos, randYPos };

	m_chicken.setPosition(randSpawn);

	m_chicken.setTexture(chickenTexture);
	m_chicken.setScale(1.5, 1.5);
	m_chicken.setOrigin(m_chicken.getGlobalBounds().left / 2, m_chicken.getGlobalBounds().height / 2);
	
	if (m_chicken.getPosition().x > randHeading.x) //setting the initial direction the chickens should travel
	{
		positiveX = false;
	}
	else if (m_chicken.getPosition().x < randHeading.x)
	{
		positiveX = true;
	}

	if (m_chicken.getPosition().y > randHeading.y)
	{
		positiveY = false;
	}
	else if (m_chicken.getPosition().y < randHeading.y)
	{
		positiveY = true;
	}
}



void enemyChickens::loadTextures()
{
	
	if (!chickenTexture.loadFromFile("resources/img/chicken_spritesheet.png"))
	{
		cout << "cant load chicken texture sheet" << endl;
	}

	if (!chickenLeftTexture.loadFromFile("resources/img/chicken_spritesheet_left.png"))
	{
		cout << "cant load chicken left texture sheet" << endl;
	}
	
	if (!chickenRightTexture.loadFromFile("resources/img/chicken_spritesheet_right.png"))
	{
		cout << "cant load chicken right texture sheet" << endl;
	}
	
	if (!chickenUpTexture.loadFromFile("resources/img/chicken_spritesheet_up.png"))
	{
		cout << "cant load chicken up texture sheet" << endl;
	}
	
	if (!chickenDownTexture.loadFromFile("resources/img/chicken_spritesheet_down.png"))
	{
		cout << "cant load chicken down texture sheet" << endl;
	}

}

void enemyChickens::wallCheck()
{
	
	if (m_chicken.getPosition().x >= ScreenSize::s_width - 30) //bouncing the chickens off of the wall
	{
		positiveX = false;
	}
	else if (m_chicken.getPosition().x <= 100)
	{
		positiveX = true;
	}


	if (m_chicken.getPosition().y >= ScreenSize::s_height - 30)
	{
		positiveY = false;
	}
	else if (m_chicken.getPosition().y <= 100)
	{
		positiveY= true;
	}
}




void enemyChickens::movement()
{	

	if (positiveX == true) //move the chickens towards their heading point
	{
		m_chicken.move(1, 0);
		randHeading.x++; // move the heading point away so the chickens will chase it forever unless they hit a wall
	}

	if (positiveX == false)
	{
		m_chicken.move(-1, 0);
		randHeading.x--;
	}

	if (positiveY == true)
	{
		m_chicken.move(0, 1);
		randHeading.y++;
	}

	if (positiveY == false)
	{
		m_chicken.move(0, -1);
		randHeading.y--;
	}

}


void enemyChickens::update(double dt)
{
	
	if (chickenState == VcChickenState::patrol)
	{
			movement();
			changeStates();
			wallCheck();
			

			if (chickenAlive == false)
			{
				m_chicken.setPosition(-20000, -20000);
			}
	}
	
}

void enemyChickens::render(sf::RenderWindow& t_window)
{
	theFeed.render(t_window);
	t_window.draw(m_chicken);
	animateChicken(currentAnimation);
}



void enemyChickens::animateChicken(VcChickenAnimState t_currentAnimation)
{
	
		if (t_currentAnimation == VcChickenAnimState::left) //check for each aniamtionState the chicken could be in
		{
			m_chicken.setTexture(chickenLeftTexture); // set the correct texture sheet
		}

		else if (t_currentAnimation == VcChickenAnimState::right)
		{
			m_chicken.setTexture(chickenRightTexture); // set the correct texture sheet
		}

		else if (t_currentAnimation == VcChickenAnimState::up)
		{
			m_chicken.setTexture(chickenUpTexture); // set the correct texture sheet
		}

		else if (t_currentAnimation == VcChickenAnimState::down)
		{
			m_chicken.setTexture(chickenDownTexture); // set the correct texture sheet
		}
		
		totalElapsed++; // add to the elapsed time

		if (totalElapsed > 32) //once its been	32 of elapsed time , reset it to 0 and add to the animation frame
		{
			totalElapsed = 0;
			animationframe++;

			if (animationframe > 3)
			{
				animationframe = 0; // restart the animation from the start of the spriteSheet with frame 0
			}

		}

		int col = animationframe % 3; // 3 columns of sprites
		int row = animationframe / 4; // 4 rows of sprites
		rectSourceSprite.height = 30; // height / width is gotten with the formula :: totalImageWidth / columns = width and  totalImageHeight / rows = height
		rectSourceSprite.width = 32;
		rectSourceSprite.left = col * rectSourceSprite.width;
		rectSourceSprite.top = row * rectSourceSprite.height;
		m_chicken.setTextureRect(rectSourceSprite);

}



void enemyChickens::changeStates() // changes animation states based on which way the chicken is facing
{
	if (positiveX == true)
	{
		currentAnimation = VcChickenAnimState::right;
	}
	
	if (positiveX == false)
	{
		currentAnimation = VcChickenAnimState::left;
	}
	
	if (positiveY == true)
	{
		currentAnimation = VcChickenAnimState::down;
	}
	
	if (positiveY == false)
	{

		currentAnimation = VcChickenAnimState::up;
	}

}

sf::Sprite enemyChickens::getBody() // simple getter for the sprite
{
	return m_chicken;
}

void enemyChickens::killChicken() // sets chickenAlive to false
{

	chickenAlive = false;
}
