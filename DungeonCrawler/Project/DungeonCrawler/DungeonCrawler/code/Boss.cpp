#include "Boss.h"

Boss::Boss()
{
	setUpSprite();
}

void Boss::setUpSprite()
{

	if (!deadbossTexture.loadFromFile("rescources/images/USED-IMAGES/deadboss.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}

	if (!bossTexture.loadFromFile("rescources/images/USED-IMAGES/boss.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	bossSprite.setTexture(bossTexture);
	bossSprite.setPosition(500, 100);
	bossSprite.setScale(2.5f, 2.5f);
	bossSprite.setOrigin(98, 50);
	if (!m_fireballBossTexture.loadFromFile("rescources/images/USED-IMAGES/fireball.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	fireBallBossSprite.setTexture(m_fireballBossTexture);
	fireBallBossSprite.setPosition(53300, 130430);
	fireBallBossSprite.setScale(0.7f, 0.7f);
	fireBallBossSprite.setOrigin(69, 55);


	if (!wipeBallBossTexture.loadFromFile("rescources/images/USED-IMAGES/wipeball.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	wipeBallBossSprite.setTexture(wipeBallBossTexture);
	wipeBallBossSprite.setPosition(400, 444100);
	wipeBallBossSprite.setScale(2.0f, 2.0f);
	wipeBallBossSprite.setColor(sf::Color::Red);
	wipeBallBossSprite.setOrigin(65, 65);


	if (!towerTexture.loadFromFile("rescources/images/USED-IMAGES/tower.png"))
	{
		std::cout << "cant load sprite" << std::endl;
	}
	for (int i = 0; i < 2;i++)
	{
		towerSprite[i].setTexture(towerTexture);
		towerSprite[i].setOrigin(75, 140);
		towerSprite[i].rotate(180);
	}

	towerSprite[0].setPosition(228, 0);
	towerSprite[1].setPosition(766, 0);



	bossHealthBar.setPosition(290, 20);
	bossHealthBar.setFillColor(sf::Color::Green);
	bossHealthBar.setOutlineThickness(10);
	bossHealthBar.setOutlineColor(sf::Color::Black);
	bossHealthBar.setSize(sf::Vector2f(m_bossHP, 20.0f));

}



void Boss::render(sf::RenderWindow& t_window)
{
	t_window.draw(towerSprite[0]);
	t_window.draw(towerSprite[1]);
	t_window.draw(bossSprite);
	t_window.draw(fireBallBossSprite);
	t_window.draw(wipeBallBossSprite);
	t_window.draw(bossHealthBar);
	t_window.draw(deadbossSprite);
}

void Boss::update(double dt)
{
	animate();
	bossSprite.move(moveSpeed, 0);
	animateFireball();

	if (m_bossHP <= 200)
	{
		bossHealthBar.setFillColor(sf::Color::Yellow);
	}
	if (m_bossHP <= 100)
	{
		bossHealthBar.setFillColor(sf::Color::Red);
	}
	if (m_bossHP > 0)
	{
		bossHealthBar.setSize(sf::Vector2f(m_bossHP, 20.0f));
	}

	if (m_bossHP <= 0 && checkBoss ==1)
	{
		deadbossSprite.setTexture(deadbossTexture);
		deadbossSprite.setScale(0.4f, 0.4f);
		deadbossSprite.setColor(sf::Color::Red);

		deadbossSprite.setPosition(bossSprite.getPosition());
		deadbossSprite.setOrigin(442, 444);

		bossHealthBar.setPosition(44444,44444);

		bossSprite.setPosition(3333333, 3333333);
		checkBoss = 2;
	}

}



void Boss::animate()
{
	if (m_bossHP > 0)
	{
		m_FrameIncrement = 0.027f; // how fast 

		m_FrameCounter += m_FrameIncrement;
		m_Frame = static_cast<int>(m_FrameCounter) % 4; // change valuues later to see the difference 
		//bossSprite.setTextureRect(sf::IntRect{ m_Frame * 191, 322, 191 , 161 }); // for 3 sprites
		bossSprite.setTextureRect(sf::IntRect{ m_Frame * 205, 510, 191 , 100 });

	}
}

void Boss::movement(int t_width, int t_height)
{
	if (m_bossHP > 0)
	{
		float minPosX = t_width - t_width + 1;
		float maxPosX = t_width - 1;

		float minPosY = t_height - t_height + 1;
		float maxPosY = t_height - 1;



		if (bossSprite.getPosition().x > maxPosX)
		{
			moveSpeed = moveSpeed * -1;
		}

		if (bossSprite.getPosition().x < minPosX)
		{
			moveSpeed = moveSpeed * -1;
		}
	}
	else {
		moveSpeed = 0;
	}
}


void Boss::animateFireball()
{
	m_fireBallFrameCounter += m_fireBallFrameIncrement;
	m_fireBallFrame = static_cast<int>(m_fireBallFrameCounter) % 5; // change valuues later to see the difference 
	fireBallBossSprite.setTextureRect(sf::IntRect{ m_fireBallFrame * 133, 3, 100 , 100 });
	wipeBallBossSprite.setTextureRect(sf::IntRect{ m_fireBallFrame * 77, 3, 77 , 80 });

}



void Boss::wipeBallMovement(sf::Vector2f pos)
{
	if (wipeBallBossSprite.getPosition().x > pos.x)
	{
		wipeBallBossSprite.move(-1, 0);
	}
	else if (wipeBallBossSprite.getPosition().x < pos.x)
	{
		wipeBallBossSprite.move(1, 0);
	}
	else if (wipeBallBossSprite.getPosition().y > pos.y)
	{
		wipeBallBossSprite.move(0, -1);
	}
	if (wipeBallBossSprite.getPosition().y < pos.y)
	{
		wipeBallBossSprite.move(0, 1);
	}
}