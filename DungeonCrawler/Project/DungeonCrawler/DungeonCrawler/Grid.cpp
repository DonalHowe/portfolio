#include "Grid.h"



class fValueComparer
{

public:
   
    bool operator()(Node* t_n1, Node* t_n2) const
    {
        return (t_n1->g_cost+t_n1->h_cost) > (t_n2->g_cost+t_n2->h_cost);
    }
};



void Grid::render(sf::RenderWindow& t_window)
{
	int count = 0;
	for (int i = 0; i < m_MAX_ROWS; i++)
	{
		for (int j = 0; j < M_MAX_COLUMNS; j++)
		{			
			t_window.draw(m_GridVec.at(j).at(i).m_rect);			
		}	
	}
	for (int i = 0; i < MAX_Nodes; i++)
	{
		t_window.draw(gridNum[i]);
	}
	if (m_vertexArray.size() > 0)
	{
		sf::VertexArray path(sf::LinesStrip, m_vertexArray.size());
		for (int i=0;i<m_vertexArray.size();i++)
		{
			path[i] = m_vertexArray.at(i);
		}
		t_window.draw(path);
	}
	

}

void Grid::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		debugLine();
	}
	
}

void Grid::setupGrid()
{	
	int num = 0;
	//int counter = 0;
	for (int i = 0; i < m_MAX_ROWS; i++)
	{
		std::vector<Node> tempVec;
		m_GridVec.push_back(tempVec);
	}
	
	for (int i = 0; i < MAX_Nodes; i++)
	{
		int x = i % m_MAX_ROWS;
		int y = i / m_MAX_ROWS;
		Node tempNode;
		
		tempNode.xPos = x;
		tempNode.yPos = y;
		tempNode.setID(x + (y * m_MAX_ROWS));
		m_GridVec.at(x).push_back(tempNode);
	}
	
	for (int i = 0; i < MAX_Nodes; i++)
	{
		setNeighbours(atIndex(i));
	}

	for (int i = 0; i < m_MAX_ROWS; i++)
	{
		
		for (int j = 0; j < M_MAX_COLUMNS; j++)
		{
			
			m_sampleNode.rectXPos = m_sampleNode.rectXPos + m_sampleNode.m_width;

			if (m_sampleNode.rectXPos > m_MAX_ROWS * m_sampleNode.m_width)
			{
				m_sampleNode.rectYPos = m_sampleNode.rectYPos + m_sampleNode.m_height;
				m_sampleNode.rectXPos = m_sampleNode.m_width;
			}
			

			m_GridVec.at(j).at(i).m_rect.setPosition(m_sampleNode.rectXPos, m_sampleNode.rectYPos);

			gridNum[num].setPosition(m_sampleNode.rectXPos, m_sampleNode.rectYPos);
			gridNum[num].setString(std::to_string(num));

			num++;
		}
	}

	m_GridVec;
}

void Grid::checkTraversable()
{
	// will set certain nodes g as greater and some as intraversable here 
	// neeed to see  where were placing the obstacles first 

	Node* tempNode;
	tempNode = atIndex(0);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(1);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(2);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(3);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(4);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(5);
	tempNode->setIntraversable(true);

	tempNode = atIndex(6);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(7);
	tempNode->setIntraversable(true);

	tempNode = atIndex(9);
	tempNode->setIntraversable(true);
	
	tempNode = atIndex(12);
	tempNode->setIntraversable(true);

	tempNode = atIndex(16);
	tempNode->setIntraversable(true);

	tempNode = atIndex(21);
	tempNode->setIntraversable(true);

	tempNode = atIndex(22);
	tempNode->setIntraversable(true);

	tempNode = atIndex(24);
	tempNode->setIntraversable(true);
	tempNode = atIndex(28);
	tempNode->setIntraversable(true);
	tempNode = atIndex(29);
	tempNode->setIntraversable(true);
	tempNode = atIndex(31);
	tempNode->setIntraversable(true);
	tempNode = atIndex(34);
	tempNode->setIntraversable(true);
	tempNode = atIndex(36);
	tempNode->setIntraversable(true);
	tempNode = atIndex(37);
	tempNode->setIntraversable(true);
	tempNode = atIndex(38);
	tempNode->setIntraversable(true);
	tempNode = atIndex(39);
	tempNode->setIntraversable(true);
	tempNode = atIndex(41);
	tempNode->setIntraversable(true);
	tempNode = atIndex(42);
	tempNode->setIntraversable(true);
	tempNode = atIndex(44);
	tempNode->setIntraversable(true);


	tempNode = atIndex(49);
	tempNode->setIntraversable(true);
	tempNode = atIndex(52);
	tempNode->setIntraversable(true);
	tempNode = atIndex(53);
	tempNode->setIntraversable(true);
	tempNode = atIndex(54);
	tempNode->setIntraversable(true);
	tempNode = atIndex(55);
	tempNode->setIntraversable(true);
	tempNode = atIndex(56);
	tempNode->setIntraversable(true);
	tempNode = atIndex(58);
	tempNode->setIntraversable(true);
	tempNode = atIndex(59);
	tempNode->setIntraversable(true);
	tempNode = atIndex(60);
	tempNode->setIntraversable(true);
	tempNode = atIndex(66);
	tempNode->setIntraversable(true);
	tempNode = atIndex(69);
	tempNode->setIntraversable(true);
	tempNode = atIndex(70);
	tempNode->setIntraversable(true);


	tempNode = atIndex(72);
	tempNode->setIntraversable(true);
	tempNode = atIndex(73);
	tempNode->setIntraversable(true);
	tempNode = atIndex(74);
	tempNode->setIntraversable(true);
	tempNode = atIndex(76);
	tempNode->setIntraversable(true);
	tempNode = atIndex(77);
	tempNode->setIntraversable(true);
	tempNode = atIndex(79);
	tempNode->setIntraversable(true);
	tempNode = atIndex(82);
	tempNode->setIntraversable(true);
	tempNode = atIndex(89);
	tempNode->setIntraversable(true);
	tempNode = atIndex(90);
	tempNode->setIntraversable(true);
	tempNode = atIndex(91);
	tempNode->setIntraversable(true);
	tempNode = atIndex(92);
	tempNode->setIntraversable(true);
	tempNode = atIndex(93);
	tempNode->setIntraversable(true);

	tempNode = atIndex(94);
	tempNode->setIntraversable(true);
	tempNode = atIndex(95);
	tempNode->setIntraversable(true);
	tempNode = atIndex(96);
	tempNode->setIntraversable(true);
	tempNode = atIndex(97);
	tempNode->setIntraversable(true);
	tempNode = atIndex(98);
	tempNode->setIntraversable(true);
	tempNode = atIndex(99);
	tempNode->setIntraversable(true);
	tempNode = atIndex(19);
	tempNode->setIntraversable(true);
	tempNode = atIndex(50);
	tempNode->setIntraversable(true);
	tempNode = atIndex(15);
	tempNode->setIntraversable(true);
	tempNode = atIndex(14);
	tempNode->setIntraversable(true);
	
}

void Grid::setUpCellIDNumText(sf::Font& m_font)
{
	for (int i = 0; i < MAX_Nodes; i++)
	{
		gridNum[i].setFont(m_font);
		gridNum[i].setFillColor(sf::Color::Green);
	}
}

void Grid::debugLine()
{

	for (int i = 0; i < aStarPath.size(); i++)
	{
		Node* tempNode=atIndex(aStarPath.at(i));
		
		int x = tempNode->m_rect.getPosition().x+ tempNode->m_rect.getSize().x/2;
		int y = tempNode->m_rect.getPosition().y+ tempNode->m_rect.getSize().y/2;
		sf::Vector2f pos = sf::Vector2f( x,y );
	
		sf::Vertex myVert(pos,sf::Color::Black);
		
		m_vertexArray.push_back(myVert);
		
	}
	int i = 0;
	
}

Grid::Grid()
{
	setupGrid();
	checkTraversable();
}

Grid::~Grid()
{
	

}

void  Grid::setNeighbours(Node *t_cell)

{
	int row = t_cell->xPos; 
	int col = t_cell->yPos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; 

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < m_MAX_ROWS && n_col >= 0 && n_col < M_MAX_COLUMNS) {

			int id = n_row +(n_col * 10);
			t_cell->setNeighbours(atIndex(id));
			//std::cout <<"ID"<<id<< " Neighbor: " << n_row << "," << n_col << ": " << std::endl;		
		}
	}
}

void Grid::setWeightLevelFour()
{
	
	
	
	for (int i = 30; i < 80; i++)
	{
		int random = rand() % 100 + 1;
		Node* tempNode = atIndex(i);
		tempNode = atIndex(i);
		tempNode->setWeightedNode(random);
		tempNode->setColorWeight();
	}
}

Node* Grid::atIndex(int t_index)
{
	int x = t_index % m_MAX_ROWS;
	int y = t_index / m_MAX_ROWS;

	return 	&m_GridVec.at(x).at(y);
}

std::stack<Node*>Grid::aStar(Node* t_startNode, Node* t_endNode,std::vector<int>& t_path, int t_level)
{
	t_path.clear();
	m_vertexArray.clear();
	m_gridStack.empty();
	Node* start = t_startNode;
	Node* goal = t_endNode;
	std::priority_queue<Node*, std::vector<Node*>, fValueComparer > pq;
	int infinity = std::numeric_limits<int>::max()/10;

	
	for (int i = 0; i < MAX_Nodes; i++)
	{
		Node* v = atIndex(i);
		v->h_cost = abs(goal->xPos - v->xPos) + abs(goal->yPos - v->yPos);
		v->SetPrevious(nullptr);
		v->setColorToTransparent();
		v->setMarked(false);
		v->g_cost = infinity;
		v->setWeightedNode(10);
		
		
		if (t_level != 4)
		{
			checkTraversable();
		}
		else if (t_level == 4)
		{
			v->setIntraversable(false);
			setWeightLevelFour();
		}
		if (v->getIntraverable() == true)
		{
			v->setIntraversableColor();
		}
		if (v->getIntraverable() == false)
		{
			v->setColorToTransparent();
		}
		std::cout << v->getWeight() << std::endl;
	}
	
	int i=0;

	start->g_cost = 0;
	//start->f_cost = 0;
	pq.push(start);

	pq.top()->setMarked(true);

	while (pq.size() != 0 && pq.top() != goal)
	{


		Node* topnode = pq.top();

		for (Node* q : topnode->GetNeighbours())
		{

			Node* child = q;
			if (child != pq.top()->GetPrevious())
			{
				
				int weight = child->getWeight();

				int distanceToChild = pq.top()->g_cost + weight;
				

				if (distanceToChild < child->g_cost&&child->getIntraverable()==false)
				{
					child->g_cost = distanceToChild;
					child->SetPrevious(pq.top());
				

				}
				if (child->getMarked() == false)
				{
					pq.push(child);
					child->setMarked(true);
				}
			}
		}

		pq.pop();
	}
	Node* pathNode = t_endNode;
	while (pathNode->GetPrevious() != nullptr)
	{
		t_path.push_back(pathNode->GetId());
		pathNode = pathNode->GetPrevious();
		m_gridStack.push(pathNode);
	}
	
	return m_gridStack;
}




