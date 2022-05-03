#pragma once

#include <iostream>

enum class GameStates {
	Menu,
	LevelOne,
	LevelTwo,
	LevelThree,
	LevelFour,
	LevelFive,
	BossLevel
};
enum class MenuStates
{
	StartGame,
	Credits,
	tutorial,
	LevelEditor,
	Inventory,
	Main

};

enum class GolemDirection
{
	Stop,
	Right,
	Left,
	Up,
	Down
};
enum class WeaponSelection
{
	sword,
	Axe,
	Nothing
};
