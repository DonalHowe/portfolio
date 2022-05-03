#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "code/ScreenSize.h"
class Node
{
	std::vector<Node*> m_neighbour;
	Node* m_previous=nullptr;
    int m_id;
	bool intraversable = false;
	int wightednode = 0;
	bool m_marked = false;
public:
	void render(sf::RenderWindow& t_window);
	Node();

	bool getIntraverable();
	void setIntraversable(bool t_setTraversable);
	sf::RectangleShape m_rect;
	void setID(int t_Id);
	int  GetId();
	void setNeighbours(Node* t_cell);
	void setPostition();
	sf::Vector2f getPosition();
	std::vector<Node*> GetNeighbours();
	int h_cost;
	int g_cost;
	int f_cost;
	int yPos;
	int xPos;
	void setWeightedNode(int t_weight);
	int getWeight();
	bool getMarked();
	const static int m_width = 90;
	const static int m_height = 90;
	int rectXPos = 0;
	int rectYPos = 0;
	void setColorToTransparent();
	void setColorWeight();
	void setIntraversableColor();


	Node* GetPrevious();
	void SetPrevious(Node * t_previous);
	void setMarked(bool t_marked);


};

