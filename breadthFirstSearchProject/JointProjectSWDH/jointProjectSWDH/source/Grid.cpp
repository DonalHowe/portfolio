#include "..\header\Grid.h"




Grid::Grid()
{
	// function that creates the map
	createMap();

	// a call to check which cells are traversable
	checkIfTraversable();
	// calls bfs and returns vector of type int which is used to get the path for the farmer to follow
	pathFindingCells= bfs(m_startArrayIndex, m_startpoint, m_endArrayIndex, m_endPoint);
	// while that cell is not empty
	while (pathFindingCells.empty() == false)
	{
		// it breaks the pair to std:: pair ints into single ints so the row and col can be couloured
		std::cout << pathFindingCells.at(pathFindingCells.size() - 1) << std::endl;
		int calcRow =pathFindingCells.at(pathFindingCells.size()-1)/10;
		int calcCol= pathFindingCells.at(pathFindingCells.size() - 1) % 10;

		if (pathNotFound == false)
		{
			gridVector.at(calcRow).at(calcCol).changeEndColour();
		}
		

		gridVector.at(calcRow).at(calcCol).changeEndColour();
		//removes the previous cell from the vector

		pathFindingCells.pop_back();
	
	}
	pathNotFound = true;
}

std::vector<int>& Grid::getPath()
{
	return path;
}

int Grid::getStartRow()
{
	return m_startArrayIndex;
}

int Grid::getStartCol()
{
	return m_startpoint;
}

int Grid::getEndRow()
{
	return m_endArrayIndex;
}

int Grid::getEndCol()
{
	return m_endPoint;
}

void Grid::update(double dt)
{
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_MAX_ROWS; i++)
	{
		for (int col = 0; col < M_MAX_COLUMNS; col++)
		{
			t_window.draw(gridVector.at(i).at(col).getRect());
		}
	}
	

}

void Grid::checkIfTraversable()
{

	Cell makeCell;
	int cellId=0;
	bool makeTrue = true;
	//for (int i = 0; i < 6; i++)
	//{
	//	cellId = std::floor(chicken.theFeed.getSprite().getGlobalBounds().width / (ScreenSize::s_width / 10)) +
	//	(std::floor(chicken.theFeed.getSprite().getGlobalBounds().height / (ScreenSize::s_height / 10)) * 10);
	////	gridVector.at(cellId).at(cellId).setTraversable(makeTrue);
	//}


	


//	// these are the static sprites and those grid are not rvaersable
	gridVector.at(3).at(6).setTraversable(makeTrue);
	gridVector.at(4).at(4).setTraversable(makeTrue);

	gridVector.at(2).at(3).setTraversable(makeTrue);
	gridVector.at(5).at(7).setTraversable(makeTrue);

	gridVector.at(8).at(8).setTraversable(makeTrue);
	gridVector.at(6).at(4).setTraversable(makeTrue);

	gridVector.at(5).at(4).setTraversable(makeTrue);
	gridVector.at(6).at(4).setTraversable(makeTrue);

	gridVector.at(5).at(8).setTraversable(makeTrue);
	gridVector.at(6).at(8).setTraversable(makeTrue);

	
}

std::vector<int> Grid::bfs(int t_startRow, int t_startCol, int t_endRow, int t_endCol)
{

	//used tp get the row and col for teh previous path
	int calc = 0;

	// the parents id 
	int parentCellId = 0;

	// current row and cell of teh bfs
	currentRow = 0;
	currentCol = 0;

	// pushes the start cell into teh queue so the algorithim can start
	bfsQueue.push(gridVector.at(t_startRow).at(t_startCol));

	// bool to stop the algorithim repeating 
	bool m_makeVisited = true;
	gridVector.at(t_startRow).at(t_startCol).setVisiited(m_makeVisited);

	// carent and child cells 
	Cell* parentNode;
	Cell* childNode;

	// a std vector fo cell pointer which is a pointer to the previouse nodes
	std::vector<Cell*> prevNodes;

	// an iterator which is used to go through the std::list
	std::list<std::pair<int,int>>::iterator it;

	if (pathNotFound == false)
	{
		gridVector.at(t_startRow).at(t_startCol).changeEndColour();
	}
	
	// store the neighbours in a list	
	


	// changes the start colour of the cell the first cell 
	gridVector.at(t_startRow).at(t_startCol).changeEndColour();


	// while the queue is not empty and the goal is not reached
	while (!bfsQueue.empty()&&goalReached==false)
	{
		// adds teh parent node into the array of nodes 
		    prevNodes.push_back(parentNode);
			// makes parent node the node from the front of the queue
			parentNode = &bfsQueue.front();
			// pops the node from teh list
			bfsQueue.pop();
			
			std::cout << "Cell :" << parentNode->getRow()<<" col" <<parentNode->getCol() << std::endl;
			// Parent cell is the cell we are expanding.
			parentCellId = (parentNode->getRow() * 10) + parentNode->getCol();
			// finds the neighbours of the current node/parent node and adds them to the list
			m_list = findNeighbours(parentNode->getRow(), parentNode->getCol());
		
				// for loop which iterates through teh list if the goal reached is false and that node is traversable
				for (it = m_list.begin(); it != m_list.end()&&goalReached==false&& parentNode->getTraversable() == false;)
				{

					// assigns current node to the neighbour					
					childNode = &gridVector.at(m_list.front().first).at(m_list.front().second);
					// want to pop the front of the list
					it++;
					// pops from the list
					m_list.pop_front();

					int i = 0;
					// if the child node is equal to the end node i.e goal is reached 
					if (childNode == &gridVector.at(t_endRow).at(t_endCol)) {
						
						std::cout << "found the endPoint" << std::endl;

						if (pathNotFound == false)
						{
							childNode->changeEndColour();
							
						}

						childNode->changeEndColour();
						// gives calc the current row int and col int which is seperated above to get the row and column of that node

						 calc = (parentNode->getRow() * 10) + parentNode->getCol() ;
						 // makes the parent node calc
						  gridVector.at(t_endRow).at(t_endCol).setParent(calc);		
						  // passes the id of that node into the path 
						  path.push_back(t_endRow * 10 + t_endCol);
						 
						  goalReached = true;
						  
					}
					else if (childNode->getVisited() == false)// makes that  node visited
					{
						childNode->setVisiited(m_makeVisited);					
						// Store a reference to the parent cell, otherwise we
						//  won't know the final path from start to end.					
						gridVector.at(childNode->getRow()).at(childNode->getCol()).setParent(parentCellId);
						bfsQueue.push(*childNode);
						std::cout << " not this node" << std::endl;
				
					}
					
				}
				
			
	}
	// used to calculate the path of the farmer
	int startingCellId = t_startRow * 10 + t_startCol ;
	// current id set to the end id
	int currentCellId = gridVector.at(t_endRow).at(t_endCol).getParent();
	// splits the parent cell id into row and column 
	int parentRow = gridVector.at(t_endRow).at(t_endCol).getParent() / 10;
	int parentCol = gridVector.at(t_endRow).at(t_endCol).getParent() % 10;
	// if the current cell does not equal the starting one the current cell id which iterates from the end to the start is stored in path
	while (currentCellId != startingCellId)
	{
		path.push_back(currentCellId);
		// stores the parent cell in an id
		currentCellId = gridVector.at(parentRow).at(parentCol).getParent();
		//gets the next parent row and column
		parentRow = gridVector.at(parentRow).at(parentCol).getParent() / 10;
		parentCol = gridVector.at(parentRow).at(parentCol).getParent() % 10;
		
	}
	return path;
	
	
}

void Grid::createMap()
{
	
	// creates a sf::vector 2f for the position so it will use the overloaded constructor
	sf::Vector2f position{ 0,0 };
	// searches the first array i.e the rows so like array[here][not this one]
	for (int row = 0; row < m_MAX_ROWS; row++)
	{
		// creates a new vector that will be added into our grid vector
		std::vector<Cell> tempVec;
		for (int col = 0; col < M_MAX_COLUMNS; col++)
		{
			// creates a cell to be added into temp vec
			Cell myCell(position);
			myCell.setRow(row);
			myCell.setCol(col);
			// adds cell into temp vec
			tempVec.push_back(myCell);
			
		
			// places the nodes across the screen 
			position.x += ScreenSize::s_width / 10;
			if (position.x >= 1440)
			{
				position.x = 0;
				position.y += ScreenSize::s_height / 10;
			}
		}
		// adds the temp vec to our grid vec 
		gridVector.push_back(tempVec);

	}
	
	
	
}
// function to find the neighbours of the current cell which is in turn returned as in a list which stores a std::pair<int>
std::list<std::pair<int, int>> Grid::findNeighbours(int t_currentRow, int t_currentCol)
{
	
	// Let's see if we can find the neighbours of row 4 and column 4:
	int row = t_currentRow; // the array in grid array
	int col = t_currentCol; // this is the object in the secons array inside of grid array
	
	
	// List all neighbors:
	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < m_MAX_ROWS && n_col >= 0 && n_col < M_MAX_COLUMNS) {

			// A valid neighbor:
			std::cout << "Neighbor: " << n_row << "," << n_col << ": "  << std::endl;
			m_tempList.push_back(std::make_pair(n_row, n_col));
		}
		
	}
	
	
	return m_tempList;

}
