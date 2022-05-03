#include "Node.h"

void Node::render(sf::RenderWindow& t_window)
{
}

Node::Node()
{
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Blue);
	m_rect.setOutlineThickness(2u);
	m_rect.setSize(sf::Vector2f{ m_width,m_height });
	m_rect.setPosition(44444, 44444);
}

bool Node::getIntraverable()
{
	return intraversable;
}

void Node::setIntraversable(bool t_setTraversable)
{
	intraversable = t_setTraversable;
}

void Node::setID(int t_int)
{
	m_id = t_int;
}

int Node::GetId() 
{
	return m_id;
}

void Node::setNeighbours(Node* t_cell)
{
	m_neighbour.push_back(t_cell);
}




void Node::setPostition()
{
}

sf::Vector2f Node::getPosition()
{
	return m_rect.getPosition();
}

std::vector<Node*> Node::GetNeighbours()
{
	return m_neighbour;
}

void Node::setWeightedNode(int t_weight)
{
	wightednode = t_weight;
}

int Node::getWeight()
{
	return wightednode;
}

bool Node::getMarked()
{
	return m_marked;
}


void Node::setColorToTransparent()
{
	m_rect.setFillColor(sf::Color::Transparent);
}

void Node::setColorWeight()
{
	m_rect.setFillColor(sf::Color::Cyan);
}

void Node::setIntraversableColor()
{
	m_rect.setFillColor(sf::Color::Red);
}

Node* Node::GetPrevious()
{
	return m_previous;
}

void Node::SetPrevious(Node* t_previous)
{
	m_previous = t_previous;
}


void Node::setMarked(bool t_marked)
{
	m_marked = t_marked;
}

