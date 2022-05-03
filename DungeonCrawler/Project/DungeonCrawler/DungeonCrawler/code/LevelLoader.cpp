#include "LevelLoader.h"

void operator >> (const YAML::Node& t_doorBackground, DoorData& t_door)
{
	t_door.position.x = t_doorBackground["position"]["x"].as<float>();
	t_door.position.y = t_doorBackground["position"]["y"].as<float>();
	t_door.size.x = t_doorBackground["size"]["x"].as<float>();
	t_door.size.y = t_doorBackground["size"]["y"].as<float>();
}


void operator >> (const YAML::Node& t_backgroundNode, BackgroundData& t_background)
{
	t_background.m_fileName = t_backgroundNode["file"].as<std::string>();
}

void operator >> (const YAML::Node& t_cageNode, CageData& t_cage)
{
	t_cage.m_fileName = t_cageNode["file"].as<std::string>();
}

void operator >> (const YAML::Node& t_torchesNode, TourchData& t_torch)
{
	t_torch.position.x = t_torchesNode["position"]["x"].as<float>();
	t_torch.position.y = t_torchesNode["position"]["y"].as<float>();
	t_torch.xScale = t_torchesNode["xScale"].as<float>();
	t_torch.yScale = t_torchesNode["yScale"].as<float>();
}

void operator >> (const YAML::Node& t_invisWallNode, boundWallsData& t_invisWalls)
{
	t_invisWalls.position.x = t_invisWallNode["position"]["x"].as<float>();
	t_invisWalls.position.y = t_invisWallNode["position"]["y"].as<float>();
	t_invisWalls.size.x = t_invisWallNode["size"]["x"].as<float>();
	t_invisWalls.size.y = t_invisWallNode["size"]["y"].as<float>();
}


void operator >> (const YAML::Node& t_mazeWallNode, mazeWallData& t_mazeWalls)
{
	t_mazeWalls.position.x = t_mazeWallNode["position"]["x"].as<float>();
	t_mazeWalls.position.y = t_mazeWallNode["position"]["y"].as<float>();
	t_mazeWalls.size.x = t_mazeWallNode["size"]["x"].as<float>();
	t_mazeWalls.size.y = t_mazeWallNode["size"]["y"].as<float>();
}



void operator >> (const YAML::Node& t_keyNode, KeyData& t_key)
{
	t_key.position.x = t_keyNode["position"]["x"].as<float>();
	t_key.position.y = t_keyNode["position"]["y"].as<float>();
	t_key.m_fileName = t_keyNode["file"].as<std::string>();
	t_key.size.x = t_keyNode["size"]["x"].as<float>();
	t_key.size.y = t_keyNode["size"]["y"].as<float>();
	
}

void operator >> (const YAML::Node& t_swordNode, SwordData& t_sword)
{
	t_sword.position.x = t_swordNode["position"]["x"].as<float>();
	t_sword.position.y = t_swordNode["position"]["y"].as<float>();
	t_sword.m_fileName = t_swordNode["file"].as<std::string>();
	t_sword.size.x = t_swordNode["size"]["x"].as<float>();
	t_sword.size.y = t_swordNode["size"]["y"].as<float>();

}

void operator >> (const YAML::Node& t_axeNode, AxeData& t_axe)
{
	t_axe.position.x = t_axeNode["position"]["x"].as<float>();
	t_axe.position.y = t_axeNode["position"]["y"].as<float>();
	t_axe.m_fileName = t_axeNode["file"].as<std::string>();
	t_axe.size.x = t_axeNode["size"]["x"].as<float>();
	t_axe.size.y = t_axeNode["size"]["y"].as<float>();

}

void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{

	const YAML::Node& torchesNode = t_levelNode["torches"].as<YAML::Node>();
	const YAML::Node& invisWallsNode = t_levelNode["invisWalls"].as<YAML::Node>();
	const YAML::Node& mazeWallsNode = t_levelNode["mazeWalls"].as<YAML::Node>();

	//const YAML::Node& doorNode = t_levelNode["door"].as<YAML::Node>();

	t_levelNode["background"] >> t_level.m_background;
	t_levelNode["cage"] >> t_level.m_cage;

  	t_levelNode["key"] >> t_level.m_key;
	t_levelNode["sword"] >> t_level.m_sword;
	t_levelNode["axe"] >> t_level.m_axe;
	t_levelNode["door"] >> t_level.m_door;

	for (int i = 0; i < torchesNode.size(); i++)
	{
		TourchData torch;
		torchesNode[i] >> torch;
		t_level.m_torches.push_back(torch);

	}

	for (int i = 0; i < invisWallsNode.size(); i++)
	{
		
		  boundWallsData  invisWalls;
		  invisWallsNode[i] >> invisWalls;
		  t_level.m_invisWallBounds.push_back(invisWalls);

	}


	for (int i = 0; i < mazeWallsNode.size(); i++)
	{

		mazeWallData  myMazeWall;
		mazeWallsNode[i] >> myMazeWall;
		t_level.m_mazeWallVec.push_back(myMazeWall);

	}

	

}

////////////////////////////////////////////////////////////
void LevelLoader::load(int t_levelNr, LevelData& t_level)
{
	std::string filename = "./rescources/levels/level" + std::to_string(t_levelNr) + ".yaml";

	
	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode>> t_level;
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


