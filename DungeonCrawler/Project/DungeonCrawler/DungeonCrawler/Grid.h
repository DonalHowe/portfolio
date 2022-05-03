#pragma once
#include <iostream>
#include "Node.h"
#include<SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <stack>

class Grid
{
	Node m_sampleNode;

	
	std::vector<sf::Vertex> m_vertexArray;

public:
	std::vector<int> aStarPath;
	void render(sf::RenderWindow& t_window);
	void update(double dt);
	void setupGrid();
	void checkTraversable();
	void setUpCellIDNumText(sf::Font& m_font);
	void debugLine();
	std::stack<Node*> m_gridStack;
	Grid();
	~Grid();
	void setNeighbours(Node* t_cell);
	void setWeightLevelFour();
	Node* atIndex(int t_index);
	std::stack<Node*> aStar(Node* t_startNode, Node* t_endNode, std::vector<int>& t_path, int t_level);
	std::vector<std::vector<Node>> m_GridVec;
	static const int MAX_Nodes = 100;
	int m_MAX_ROWS = 10;
	int M_MAX_COLUMNS = 10;

	sf::Text gridNum[MAX_Nodes];

};

