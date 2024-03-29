#include "LevelLoader.h"

/// The various operator >> overloads below are non-member functions used to extract
///  the game data from the YAML data structure.

/// <summary>
/// @brief Extracts the obstacle type, position and rotation values.
/// 
/// </summary>
/// <param name="t_obstacleNode">A YAML node</param>
/// <param name="t_obstacle">A simple struct to store the obstacle data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_obstacleNode, ObstacleData& t_obstacle)
{
	t_obstacle.m_type = t_obstacleNode["type"].as<std::string>();
	t_obstacle.m_position.x = t_obstacleNode["position"]["x"].as<float>();
	t_obstacle.m_position.y = t_obstacleNode["position"]["y"].as<float>();
	t_obstacle.m_rotation = t_obstacleNode["rotation"].as<double>();
}
void operator >> (const YAML::Node& t_enemyNode, EnemyData& t_enemies)
{
	t_enemies.m_type = t_enemyNode["type"].as<std::string>();
	t_enemies.m_position.x = t_enemyNode["position"]["x"].as<float>();
	t_enemies.m_position.y = t_enemyNode["position"]["y"].as<float>();
	t_enemies.m_duration = t_enemyNode["duration"].as<int>();
}

/// <summary>
/// @brief Extracts the filename for the game background texture.
/// 
/// </summary>
/// <param name="t_backgroundNode">A YAML node</param>
/// <param name="t_background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_backgroundNode, BackgroundData& t_background)
{
	t_background.m_fileName = t_backgroundNode["file"].as<std::string>();
}

/// <summary>
/// @brief Extracts the initial screen position for the player tank.
/// 
/// </summary>
/// <param name="t_tankNode">A YAML node</param>
/// <param name="t_tank">A simple struct to store data related to the player tank</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_tankNode, TankData& t_tank)
{
	t_tank.m_postion.x= t_tankNode["position"]["x"].as<float>();
	t_tank.m_postion.y = t_tankNode["position"]["y"].as<float>();
	t_tank.m_scale = t_tankNode["scale"].as<float>();
	t_tank.rotation = t_tankNode["rotation"].as<float>();
	
}




/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// Invokes other functions to extract the background, tank and obstacle data.
//   Because there are multiple obstacles, obstacle data are stored in a vector.
/// </summary>
/// <param name="t_levelNode">A YAML node</param>
/// <param name="t_level">A simple struct to store level data for the game</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	
	// background is a simple mapping
	t_levelNode["background"] >> t_level.m_background;
	

	// tank is a simple mapping, no loop required
     	

	// This is incorrect, tank is not a sequence:
	
	t_levelNode["tank"] >> t_level.m_tank;
	t_levelNode["ai_tank"] >>t_level.m_aiTank;

	// This is correct as obstacles is a sequence
	const YAML::Node& obstaclesNode = t_levelNode["obstacles"].as<YAML::Node>();
	
	
	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{
		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		t_level.m_obstacles.push_back(obstacle);
	}
	
	const YAML::Node& enemiesNode = t_levelNode["enemies"].as<YAML::Node>();

	for (unsigned i = 0; i < enemiesNode.size(); ++i)
	{
		EnemyData enemy;
		enemiesNode[i] >> enemy;
		t_level.m_enemies.push_back(enemy);
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::load(int t_levelNr, LevelData& t_level)
{
	std::string filename = "./resources/levels/level" + std::to_string(t_levelNr) + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}


