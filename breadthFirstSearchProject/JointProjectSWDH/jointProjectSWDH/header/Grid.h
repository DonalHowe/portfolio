#pragma once

#include "Cell.h"
#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <vector>
#include "enemyChickens.h"
#include "ScreenSize.h"



class Grid
{
	// the chicken object to access the chicken feed
	enemyChickens chicken;
	// teh queue
	std::queue<Cell> bfsQueue;
	// function to create the map
	void createMap();
	// end point for the bfs and startpoint
	int m_endPoint=6;
	int m_endArrayIndex=8;
	int m_startArrayIndex=3;
	int m_startpoint=0;
	// the list functioun which returns the neighbours
	std::list<std::pair<int,int>> findNeighbours(int t_currentCellArray, int t_currentCellobject);
	// max rows colls
	const static int  m_MAX_ROWS = 10;
	const static int  M_MAX_COLUMNS = 10;
	// the list which we cycle through for bfs
	std::list<std::pair<int,int>> m_list;
	// teh current row and col of the bfs
	int currentRow;
	int currentCol;
	// teh temp list 
	std::list<std::pair<int, int>> m_tempList;
	// the vector which store the cells that are used for the player path
	std::vector<int> pathFindingCells;
	// the number of rows
	int n_row;
	int n_col;
	// the final goal for teh bfs bool
	bool goalReached = false;
	// teh function to check if the cell is traversable 
	void checkIfTraversable();
	// teh path which stores an int which is teh cell id
	std::vector<int> path;

public:

	// getters and setters
	bool pathNotFound = false;
	std::vector<int>& getPath();

	int getStartRow();
	int getStartCol();
	int getEndRow();
	int getEndCol();
	
	int endRow ;
	int endCol ;
	Grid();
	// the grid vector which stores arrays which in turn store cell objects
	std::vector<std::vector<Cell>> gridVector;
	void update(double dt);
	void render(sf::RenderWindow& t_window);
	// teh bfs function which performs the bfs
	std::vector<int>  bfs(int t_startArrayIndex, int t_startPoint, int t_endArrayIndex, int t_endPoint);

	//std::map<int, Cell> Map;
	
	

	

};

