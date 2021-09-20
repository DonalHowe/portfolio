#include "..\header\Player.h"


float Player::getPlayerSpeed()
{
	return m_playerSpeed;
}

void Player::setPlayerSpeed(float t_playerSpeed)
{
	m_playerSpeed = t_playerSpeed;
}

Player::Player()
{
	loadFiles();
	initialise();
	
}

void Player::loadFiles()
{
	if (!playerTexture.loadFromFile("resources/img/fox_spritesheet_2.png")) //spritesheets for all the directions
	{
		std::cout << "Error with player file";
	}

	if (!playerUpTexture.loadFromFile("resources/img/fox_spritesheet_up.png"))
	{
		std::cout << "Error with player up file";
	}
	
	if (!playerDownTexture.loadFromFile("resources/img/fox_spritesheet_down.png"))
	{
		std::cout << "Error with player down file";
	}
	
	if (!playerLeftTexture.loadFromFile("resources/img/fox_spritesheet_left.png"))
	{
		std::cout << "Error with player left file";
	}
	
	if (!playerRightTexture.loadFromFile("resources/img/fox_spritesheet_right.png"))
	{
		std::cout << "Error with player right file";
	}

}


void Player::initialise()
{
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(200, 200);

}



void Player::update(double dt)
{
	movePlayer();
}

void Player::draw(sf::RenderWindow& t_window)
{

  t_window.draw(playerSprite);
  animatePlayer(animationState);
 
}


void Player::movePlayer()
{
     playerPos = playerSprite.getPosition();
	 playerSprite.setScale(2, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerPos.y-= m_playerSpeed;
		animationState = PlayerAnimations::up; // setiing the states of the player when they are up down left or right 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerPos.x-= m_playerSpeed;
		animationState = PlayerAnimations::left;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerPos.y+= m_playerSpeed;
		animationState = PlayerAnimations::down;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerPos.x+= m_playerSpeed;
		animationState = PlayerAnimations::right;
	}

	
	playerSprite.setPosition(playerPos);
}

void Player::animatePlayer(PlayerAnimations t_playerAnimState)
{
	if (t_playerAnimState == PlayerAnimations::up)
	{
		playerSprite.setTexture(playerUpTexture); // set the correct texture sheet
	}
	else if (t_playerAnimState == PlayerAnimations::down)
	{
		playerSprite.setTexture(playerDownTexture); // set the correct texture sheet
	}
	else if (t_playerAnimState == PlayerAnimations::left)
	{
		playerSprite.setTexture(playerLeftTexture); // set the correct texture sheet
	}
	else if (t_playerAnimState == PlayerAnimations::right)
	{
		playerSprite.setTexture(playerRightTexture); // set the correct texture sheet
	}

	totalElapsed++;
	
	if (totalElapsed > 16)
	{
		totalElapsed = 0;
		animationframe++;

		if (animationframe > 3)
		{
			animationframe = 0;
		}

	}
	
	int col = animationframe % 3; // 3 columns of sprites
	int row = animationframe / 4; // 4 rows of sprites
	rectSourceSprite.height = 25; // height / width is gotten with the formula :: totalImageWidth / columns = width and  totalImageHeight / rows = height
	rectSourceSprite.width = 47;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	playerSprite.setTextureRect(rectSourceSprite);
}


sf::Sprite Player::getBody() // simple getter
{
	return playerSprite;
}


