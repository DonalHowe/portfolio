#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include "GameStates.h"


/// <summary>
/// @brief A struct to store Background texture information.
/// 
/// </summary>
struct BackgroundData
{
	std::string m_fileName;
};


struct CageData
{
	std::string m_fileName;
};

struct TourchData
{
	sf::Vector2f position;
	float xScale;
	float yScale;
};

struct KeyData
{
	sf::Vector2f position;
	std::string m_fileName;
	sf::Vector2f size;
	
};

struct SwordData
{
	sf::Vector2f position;
	std::string m_fileName;
	sf::Vector2f size;

};

struct AxeData
{
	sf::Vector2f position;
	std::string m_fileName;
	sf::Vector2f size;

};



struct DoorData
{
	sf::Vector2f position;
	sf::Vector2f size;
};

struct boundWallsData
{
	sf::Vector2f position;
	sf::Vector2f size;
};

struct mazeWallData
{
	sf::Vector2f position;
	sf::Vector2f size;
};



struct LevelData
{
	BackgroundData m_background;
	CageData m_cage;

	std::vector< TourchData > m_torches;
	std::vector< boundWallsData > m_invisWallBounds;
	SwordData m_sword;
	DoorData m_door;
	KeyData m_key;
	AxeData m_axe;
	std::vector< mazeWallData > m_mazeWallVec;

};

/// <summary>
/// @brief A class to manage level loading.
/// 
/// This class will manage level loading using YAML.
/// </summary>
class LevelLoader
{
public:

	/// <summary>
	/// @brief No-op default constructor.
	/// 
	/// </summary>
	LevelLoader() = default;
	GameStates gStates;
	/// <summary>
	/// @brief Loads and parses the yaml level file.
	/// The level file is identified by a number and is assumed to have
	/// the following format: "level" followed by number followed by .yaml extension
	/// E.g. "level1.yaml"
	/// The level information is stored in the specified LevelData object.
	/// If the filename is not found or the file data is invalid, an exception
	/// is thrown.
	/// </summary>
	/// <param name="t_levelNr">The level number</param>
	/// <param name="t_level">A reference to the LevelData object</param>
	static void load(int t_levelNr, LevelData& t_level);
};