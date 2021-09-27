#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
#pragma comment(lib,"libyaml-cppmdd") 
// Add this line under the #ifdef _DEBUG directive (for Debug builds)
#pragma comment(lib,"thor-d.lib") 

// Add this line under the #else directive (for Release builds)
#pragma comment(lib,"thor.lib") 

#include "Game.h"
#include "LevelLoader.h"

/// <summary>
/// @brief starting point for all C++ programs.
/// 
/// Create a game object and run it.
/// </summary>
/// <param name=""></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int, char* argv[])
{
	Game game;
	LevelData levelData;
	int levelNr = 1;
	LevelLoader::load(levelNr, levelData);

	game.run();
}