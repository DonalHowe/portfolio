// DungeonCrawler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"thor-d.lib") 

#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"thor.lib") 

#endif 

#pragma comment(lib,"libyaml-cppmdd") 

#include <iostream>
#include "code/Game.h"
#include "code/LevelLoader.h"

int main()
{
    Game game;
    game.run();

    LevelData levelData;
    int levelNr = 1;
    LevelLoader::load(levelNr, levelData);

};


