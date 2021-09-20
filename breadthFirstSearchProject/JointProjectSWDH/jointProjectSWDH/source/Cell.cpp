#include "..\header\Cell.h"

Cell::Cell(sf::Vector2f t_position): m_WIDTH(ScreenSize::s_width/10),m_HEIGHt(ScreenSize::s_height/10)
, m_visited(false), m_traversable(false), m_Pos(t_position)
{
	m_rect.setSize(sf::Vector2f{ m_WIDTH,m_HEIGHt });
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1u);
	m_rect.setOutlineColor(sf::Color::Blue);
	m_rect.setPosition(m_Pos);
	
	
}



void Cell::update(double dt)
{
}

Cell::Cell(): m_WIDTH(ScreenSize::s_width / 10), m_HEIGHt(ScreenSize::s_height / 10)
{
}

bool Cell::getTraversable()
{
	return m_traversable;
}

int Cell::getRow()
{
	return m_row;
}

int Cell::getCol()
{
	return m_col;
}

void Cell::setRow(int t_Row)
{
	m_row = t_Row;
	
}

void Cell::setCol(int t_col)
{
	m_col = t_col;
}


void Cell::setVisiited(bool t_changeValue)
{
	m_visited = t_changeValue;
}

bool Cell::getVisited()
{
	return m_visited;
}

void Cell::setTraversable(bool t_changeValue)
{
	m_traversable = t_changeValue;
}

void Cell::resetColour()
{
	m_rect.setFillColor(sf::Color::Transparent);
}

void Cell::changeEndColour()
{
	m_rect.setFillColor(sf::Color::Red);
}

int Cell::getParent()
{
	return m_parent;
}

void Cell::setParent(int t_parent)
{
	m_parent = t_parent;
}



sf::RectangleShape Cell::getRect()
{
	return m_rect;
}
