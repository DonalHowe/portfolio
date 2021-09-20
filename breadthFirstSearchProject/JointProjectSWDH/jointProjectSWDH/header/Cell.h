#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"

// what we need 
/// bool to show if traversable
// size of each node on the map
//we are implementing spatial partition
// each node is 144 width with 90 height 
// we are using a 10 by 10 grid

class Cell
{
public:
	// cell constructor
	Cell(sf::Vector2f t_position);
	void update(double dt);
	Cell();
	//function to return iof the cell is traversable
	bool getTraversable();
	//getter and setter functions
	int getRow();
	int getCol();
	void setRow(int t_row);
	void setCol(int t_col);
	void setVisiited(bool t_changeValue);
	bool getVisited();
	void setTraversable(bool t_changeValue);
	//reset teh colour of the tiles
	void resetColour();
	// change teh end and startColour
	void changeEndColour();
	// function to get teh parent of the cell
	int getParent();
	void setParent(int t_parent);
	
	sf::Vector2f m_Pos;// the position of the nodes

	sf::RectangleShape getRect();

private:
	// collumn and row 
	int m_col;
	int m_row;
	// parent int
	int m_parent;
	const   float 	m_WIDTH;// the width of the node
	const   float   m_HEIGHt;// the height of the node

	bool m_traversable;// if the node is traversable by the farmer

	bool m_visited;// if the node has been visited

	sf::RectangleShape m_rect;// the rect to visualise the node
	
	

	
};

