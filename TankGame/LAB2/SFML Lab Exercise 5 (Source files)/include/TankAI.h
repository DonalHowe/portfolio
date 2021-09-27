#pragma once
#include "MathUtility.h"
#include "Tank.h"
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include <iostream>
#include <queue>
#include "CollisionDetector.h"
#include <Thor/Shapes.hpp>




class TankAi
{
public:
	/// <summary>
	/// @brief Constructor that stores a reference to the obstacle container.
	/// Initialises steering behaviour to seek (player) mode, sets the AI tank position and
	///  initialises the steering vector to (0,0) meaning zero force magnitude.
	/// </summary>
	/// <param name="texture">A reference to the sprite sheet texture</param>
	///< param name="wallSprites">A reference to the container of wall sprites</param>
	TankAi(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites);

	/// <summary>
	/// @brief Steers the AI tank towards the player tank avoiding obstacles along the way.
	/// Gets a vector to the player tank and sets steering and velocity vectors towards
	/// the player if current behaviour is seek. If behaviour is stop, the velocity vector
	/// is set to 0. Then compute the correct rotation angle to point towards the player tank. 
	/// If the distance to the player tank is < MAX_SEE_AHEAD, then the behaviour is changed from seek to stop.
	/// Finally, recalculate the new position of the tank base and turret sprites.
	/// </summary>
	/// <param name="playerTank">A reference to the player tank</param>
	/// <param name="dt">update delta time</param>
	void update(Tank const& playerTank, double dt);

	/// <summary>
	/// @brief Draws the tank base and turret.
	///
	/// </summary>
	/// <param name="window">The SFML Render window</param>
	void render(sf::RenderWindow& window);

	/// <summary>
	/// @brief Initialises the obstacle container and sets the tank base/turret sprites to the specified position.
	/// <param name="position">An x,y position</param>
	/// </summary>
	void init(sf::Vector2f position);

	enum class AiType
	{
		AI_ID_NONE,
		AI_ID_SEEK_SHOOT_AT_PLAYER
	};
	sf::Vector2f seek(sf::Vector2f playerPosition) const;
	bool collidesWithPlayer(Tank const& playerTank) const;
	int m_AiTankHealth = 1;
	void applyDamage(int t_damageAmount);
	sf::Sprite getTankBase();
	// the tanks state

private:

	void initSprites();

	void updateMovement(double dt);

	void initVisionCone(float t_angle);
	void updateVisionCone(Tank const& playerTank);
	int incrementMovement = 0;
	sf::Vector2f randDirection{0,0};
	bool tankSeekCondition = false;
	void boundaryCheck();
	int randomX = 0;
	int randomY = 0;
	float area1 = 0.0f;

	float area2 = 0.0f;

	float area3 = 0.0f;

	float areaOrig=0.0f;

	bool isLeft(sf::Vector2f t_linePoint1, sf::Vector2f t_linePoint2, sf::Vector2f t_point) const;
	bool isRight(sf::Vector2f t_linePoint1, sf::Vector2f t_linePoint2, sf::Vector2f t_point) const;
	sf::Vector2f headingTotal = {0.0f, 0.0f};
	//void updateVisionCone(sf::Vector2f playerPosition);
	sf::Vector2f m_visionConeLeft;
	sf::Vector2f m_visionConeRight;

	sf::Vector2f leftLineStartPoint{};
	sf::Vector2f leftLineEndPoint{};
	sf::Vector2f leftVector{};

	thor::Arrow m_arrowLeft;
	thor::Arrow m_arrowRight;


	// Vision cone vector...initially points along the x axis.
	sf::Vector2f m_visionConeDir{ 1, 0 };

	static constexpr float VISION_CONE_LENGTH{ 200.0f };

	sf::Vector2f collisionAvoidance();

	const sf::CircleShape findMostThreateningObstacle();

	// A reference to the sprite sheet texture.
	sf::Texture const & m_texture;

	// A sprite for the tank base.
	sf::Sprite m_tankBase;

	// A sprite for the turret
	sf::Sprite m_turret;
	
	// A reference to the container of wall sprites.
	std::vector<sf::Sprite> & m_wallSprites;

	// The current rotation as applied to tank base and turret.
	double m_rotation{ 0.0 };
	const float MASS = 5.0f;
	// Current velocity.
	sf::Vector2f m_velocity;

	// Steering vector.
	sf::Vector2f m_steering;

	// The ahead vector.
	sf::Vector2f m_ahead;

	// The half-ahead vector.
	sf::Vector2f m_halfAhead;

	// The maximum see ahead range.
	static float constexpr MAX_SEE_AHEAD{ 50.0f };

	// The maximum avoidance turn rate.
	static float constexpr MAX_AVOID_FORCE{ 50.0f };

	// 
	static float constexpr MAX_FORCE{ 10.0f };

	// The maximum speed for this tank.
	float MAX_SPEED = 10.0f;

	// A container of circles that represent the obstacles to avoid.
	std::vector<sf::CircleShape> m_obstacles;

	enum class AiBehaviour
	{
		SEEK_PLAYER,
		PATROL_PLAYER,
		STOP
	} m_aiBehaviour;


};

