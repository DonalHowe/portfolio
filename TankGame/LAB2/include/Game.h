#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Tank.h"
#include <string>
#include"Enemies.h"


#include "SFML/Audio.hpp"
#include "SFML Lab Exercise 5 (Source files)/include/TankAI.h"
#include "gameState.h"
#include "HUD.h"




/// <summary>
/// @author RP
/// @date September 2020
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();
	LevelData m_level;
	Tank m_tank;
	Enemies m_enemies;
	GameState m_gameState{ GameState::GAME_RUNNING };
	// The font to be used for the HUD.
	sf::Font m_font;
	
	// The game HUD instance.
	HUD m_hud;


	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();




protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();
	void collsionDectection();


	sf::Sprite  m_fuel;
	sf::Texture m_fuelTexture;
	sf::Text tank_fuel_text;
	sf::Sprite m_prize;
	sf::Texture m_prizeTexture;

	
	sf::Clock clock;
	// the text to read  clock for the game
	sf::Text clockTextTimer;

	// text for the accuracy
	sf::Text accuracyText;
	sf::Text ScoreText;

	// game over text
	sf::Text gameOver;
	sf::Text gameWin;
	// bools to do collsion buffer
	bool bulletCollided = false;
	bool bulletLeft = false;
	bool gamefinished=false;
	int timerCut = 0;// this takes the sf::clock time and truncates it to get rid of .9767 etc
	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	/// 
	void processGameEvents(sf::Event&);
	std::vector<sf::Sprite> m_wallSprites;
	sf::Vector2f theBulletsFinalDirection;
	void generateWalls();
	// main window
	sf::RenderWindow m_window;
	std::vector<sf::Sprite> m_spriteVector;
	sf::Texture m_spriteSheetTexture;
	std::function<void(int)> m_funcApplyDamage;
	sf::RectangleShape goalLocation;
	int possibleLocation = 0;
	sf::Vector2f locationOne{ 100,100 };
	sf::Vector2f locationTwo{ 500,300 };
	sf::Vector2f locationThree{ 600,400 };
	sf::Vector2f locationFour{ 90,550 };
	sf::Vector2f locationFive{ 150,650 };
	
	bool goalAchieved = false;
	float m_fuelLeak = .5;
	// Player tank sprite and texture all the sprites and textures
	
	// texture for the tank and bullet etc
	sf::Texture m_texture;
	//background sprite
	sf::Sprite m_BackGroundSprite;

	sf::Texture m_backGroundTexture;

	sf::Sprite m_obstacleSprite;

	sf::Texture m_obtacleTexture;
	// the cuntion to calculate the accuracy of the player
	void accuracyCalc();
	// amount of shots fired by the player
	float shotsFired;
	// the total accuracy of the player
	float totalAcuracy;
	// the amount of enemies shot by the player
	int enemiesShot;
	TankAi m_aiTankOne;
	int m_gameDelay;
	bool m_aireleaseTank = false;

	// setting up of the line arrow
	void setupLine();
	//sound ariables
	sf::SoundBuffer m_enemyDeathSoundABuffer;
	sf::Sound m_enemyDeathSound;
	// variables to setup the line for the direction arrow
	sf::VertexArray m_tankLine{ sf::Lines };
	sf::Vertex m_tankLineStart;
	sf::Vertex m_tankLineEnd;
	sf::CircleShape m_directionTriangle{ 20,3 };
	
	bool lineDrawn = false;

};
