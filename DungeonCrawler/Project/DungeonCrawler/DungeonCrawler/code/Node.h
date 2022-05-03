#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include 
class Node
{
	sf::RectangleShape m_rect;
	std::list<Node> m_neighbour;
	static const int  m_width;
	static const int  m_height;
public:
	void render(sf::RenderWindow& t_window);
	Node();
	void setID();
	int GetId();
	void setNeighbours();
	std::list<Node> GetNeighbours();
};

