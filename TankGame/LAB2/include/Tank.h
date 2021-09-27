#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include <algorithm>
#include "CollisionDetector.h"
#include "Bullet.h"

#include "SFML/Audio.hpp"
#include "ScreenSize.h"
#include "SFML Lab Exercise 5 (Source files)/SFML Lab Exercise 7 (Source files)/ProjectilePool.h"





/// <summary>
/// @brief A simple tank controller.
/// author: donal howe
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
	
public:
	void increaseSpeed();
	void decreaseSpeed();
	void increseRotaion();
	void decreaseRotation();
	void turretRotaion();
	void turrertRotaionAnti();
	void handleKeyInput();
	void deflect();
	Tank(sf::Texture const& texture, std::vector<sf::Sprite> &m_wallSprites);
	bool checkWallCollision();
	void update(double dt,sf::Vector2f &t_pos,int &t_rotation, std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase);
	void render(sf::RenderWindow& window);
	void setPosition(sf::Vector2f t_pos);
	void setRotation(double t_rotation);
	bool offScreen();
	void centreTurret(double t_rotation);
	void adjustRotation();
	sf::Vector2f getPosition() const;
	
	/*Bullet tankBullet;*/
	ProjectilePool m_pool;

	int m_tankFuel = 100000;


	void boundaryCheck();
	sf::Vector2f pos{ 0,0 };
	/// <summary>
	/// @brief Generates a request to fire a projectile.
	/// A projectile will be fired from the tip of the turret only if time limit between shots
	///  has expired. Fire requests are not queued.
	/// </summary>
	void requestFire();

	bool hasBeenCentred = false;
	bool m_enableRotation=true;
	float rotRadiand = 0.0f;
	
	
	
	double m_previousSpeed;
	double m_speed=0;
	double m_rotation;
	double m_Turretrotation;
	double m_previousRotation;
	double m_previousTurretRotation;

	sf::Vector2f m_bulletDirection;
	
	std::vector<sf::Sprite>& m_wallSprites;
	sf::Vector2f m_previousPosition;
	sf::Texture const& m_texture;

	sf::Vector2f m_position{ 500.0f,300.0f };

	sf::Sprite getTankBase() const;
	sf::Sprite getTankTurret() const;

private:
	void initSprites();
	sf::Sprite m_turret;
	sf::Sprite m_tankBase;

	
	sf::RectangleShape m_rectangleBase;
		
};
