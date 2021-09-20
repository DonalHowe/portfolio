#pragma once

// the player animations and the gamesStte for the actual game
enum class GameState
{
	
	gamePlay,
	ending,
	Start,
	instructions,
	credits,
	maps,
	winning
};

enum class PlayerAnimations
{
	walk,
	idle,
	jump,
	slipping,
	left,
	right,
	up,
	down
};



