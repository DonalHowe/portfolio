#pragma once

#include <SFML/Graphics.hpp>
#include "GameStates.h"
#include "Player.h"
#include "ScreenSize.h"
#include "MainMenu.h"
#include "Grid.h"
#include "LevelLoader.h"
#include "Key.h"
#include "DumbEnemy.h"
#include "WalkerEnemy.h"
#include "mazeGuide.h"
#include "ParticleSystem.h"
#include "ParticleBoss.h"

#include "Boss.h"




class Game
{
public:

	Player playerOne;
	MainMenu m_menu;
	Grid myGrid;
	Key myKey;
	mazeGuide m_mazeGuide;
	Inventory myInventory;
	DumbEnemy dummyEnemy;
	WalkerEnemy golemEneny;
	ParticleSystem particlesSystem;
	Particle particles;

	ParticleSystemBoss particlesSystemBoss;


	Boss boss;
	std::vector<WalkerEnemy> walkerVector;
	Game();
	void run();
	GameStates m_gameStateSwitcher = { GameStates::Menu };
    WeaponSelection m_WeaponSwitcher= { WeaponSelection::Nothing };
	bool backToMenu = false;
	bool aStarRun = false;
	sf::Texture m_keyTexture;
	sf::RenderWindow m_window;
	sf::Font m_babaFont;
	bool collectedKey = false;
	bool collectedSword = false;
	bool collectedAxe = false;
	sf::RectangleShape wipeAttackBar;
	sf::RectangleShape wipeAttackBarOutlineFixed;

	sf::SoundBuffer m_axeSoundsBuffer;
	sf::Sound m_axeSounds;

	sf::SoundBuffer m_dragonFireSoundBuffer;
	sf::Sound m_dragonFireSound;


	bool usingAxe = false;
	bool usingSword = false;
	sf::View view2;

	bool hasLevelLoaded = false;

	int levelTwoEnemyLives = 0;
	int checkForFairy = 0;

protected:
	//Controls animation
	float m_playerFrameIncrement{ 0.028f }; // how fast 
	float m_playerFrameCounter{ 0.0f };
	int m_playerFrame{ 0 };
	int levelCheckForLvl3 = 1;
	int levelCheckForLvl4 = 1;
	float angleShot2 = 0.0f;
	float angleShot3 = 0.0f;
	int randTower = 11;
	int gameTimer = 0;
	int bossShotRandomNum = 0;
	int howOftenBossAttacks = 2500; // THE LESS NUMBERS IS THE MORE EXTREME IT WILL BE. DONT DO LOWER THAN 10 OR NOT GONNA WORK DUE TO MY INTENDED RULE
	int tempWallPos = 0;

	bool levelEditor = false;
	bool editorBeingUsed = false;
	/////////////
	LevelData m_level;
	sf::RectangleShape startLevelDoor;
	sf::RectangleShape cageTop[3];
	std::vector <sf::RectangleShape> mazeWalls;
	sf::CircleShape mazeExit;

	sf::RectangleShape columnSquare[4];

	std::vector <sf::RectangleShape> invisWallVec;
	sf::RectangleShape m_tempRect;
	sf::Vector2i m_mousePos;


	std::vector <sf::Sprite> torchSpriteVec;
	sf::Sprite roomOneBackgroundSp;
	sf::Texture roomOneTexture;
	sf::Texture torchTexture;
	sf::Sprite roomOneCageSprite;
	sf::Sprite puddleOneSprite[2];
	sf::Texture puddleTexture;
	sf::Sprite circleSprite;
	sf::Texture circleTexture;

	sf::Texture roomOneCageTexture;
	sf::Text levelOneInfo;
	sf::Text levelTwoInfo;
	sf::Text levelThreeInfo;


	int levelNum;
	void loadLevel(int t_levelId);

	void update(double dt);
	
	void render();

	void processEvents();
	void processGameEvents(sf::Event& t_event);
	void setUpSprites();
	void animateSprite();
	void collisions();
	void boosAttack();
	void bossPathfindAttack();
	void selectWeapons();
	void musicInitiliser();
	void levelEditorMaze();
	bool isTowerSelected = false;
};
