/// author : donal Howe
/// 

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "EditedGrid" }, m_exitGame{ false },
	m_windowTwo{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Menu" },
	m_windowAstar{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Dstar" }
{
	
}


Game::~Game()
{
	
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); 
	while (m_window.isOpen())
	{
		processEvents(); 
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render(); 
	}
}

// sets random start and end pos for the algorithms to avoid positional bias
void Game::TestingMode()
{
	srand((time(NULL)));
	if (m_gridSizeState == GridSize::small)
	{

		m_tempstart = m_grid.atIndex(rand() % 2200 + 1);
		m_tempsEnd = m_grid.atIndex(rand() % 2200 + 1);


	}

	if (m_gridSizeState == GridSize::large)
	{
		m_tempstart = m_grid.atIndex(rand() % 6000 + 1);
		m_tempsEnd = m_grid.atIndex(rand() % 6000 + 1);

	}

	if (m_gridSizeState == GridSize::veryLarge)
	{
		m_tempstart = m_grid.atIndex(rand() % 20000 + 1);
		m_tempsEnd = m_grid.atIndex(rand() % 20000 + 1);
	}


}

// runs the selected algorithm with the chosen start and end positions and runs dstar lite on the other screen if
// that option is seleceted
// also stores the times in the excell file
void Game::PlayMode()
{

	if (m_SrtChosen == true && m_EndChosen == true)
	{

		m_tempstart = m_grid.atIndex(m_startCelI_Id);
		m_tempsEnd = m_grid.atIndex(m_EndCell_Id);
		m_tempstartTwo = m_gridTwo.atIndex(m_startCellTwo_Id);
		m_tempsEndTwo = m_gridTwo.atIndex(m_EndCellTwo_Id);

		/// <summary>
		///  testing for Astar
		/// </summary>
		/// <param name="t_deltaTime"></param>
		if (m_switcher == WhichAlgorithm::Astar)
		{
			if (temp == false)
			{
				m_astar.computeShortestPath(m_tempstart, m_tempsEnd, &m_grid);
				
			}
			

			if (m_gridSizeState == GridSize::small)
			{
				std::string AstarResult = std::to_string((m_astar.getTimer().asSeconds()));
				std::ofstream outputData("AstarTime.csv", std::ios::app);
				outputData << AstarResult << std::endl;
				outputData.close();

			}
			else if (m_gridSizeState == GridSize::large)
			{
				std::string AstarResult = std::to_string((m_astar.getTimer().asSeconds()));
				std::ofstream outputData("AstarTimeMedium.csv", std::ios::app);
				outputData << AstarResult << std::endl;
				outputData.close();

			}
			else if (m_gridSizeState == GridSize::veryLarge)
			{
				std::string AstarResult = std::to_string((m_astar.getTimer().asSeconds()));
				std::ofstream outputData("AstarTimeLarge.csv", std::ios::app);
				outputData << AstarResult << std::endl;
				outputData.close();

			}

		}
		/// <summary>
		///  testing for Dstar Lite
		/// </summary>
		/// <param name="t_deltaTime"></param>
		if (m_switcher == WhichAlgorithm::DstarLite)
		{

			if (temp == false)
			{
				m_dStarLite.DstarLiteMain(m_tempstart, m_tempsEnd, &m_grid);
				
			}
			



			if (m_gridSizeState == GridSize::small)
			{
				std::string message = "small";
				std::string DstarResult = std::to_string((m_dStarLite.getTimer().asSeconds()));
				std::ofstream outputData("DstarTime.csv", std::ios::app);
				outputData << message << DstarResult << std::endl;
				outputData.close();

			}

			else if (m_gridSizeState == GridSize::large)
			{

				std::string message = "medium";
				std::string DstarResult = std::to_string((m_dStarLite.getTimer().asSeconds()));
				std::ofstream outputData("DstarTimeMedium.csv", std::ios::app);
				outputData << message << DstarResult << std::endl;
				outputData.close();

			}

			else if (m_gridSizeState == GridSize::veryLarge)
			{


				std::string message = "large";
				std::string DstarResult = std::to_string(m_dStarLite.getTimer().asSeconds());
				std::ofstream outputData("DstarTimeLarge.csv", std::ios::app);
				outputData << message << DstarResult << std::endl;
				outputData.close();


			}



		}

		/// <summary>
		///  testing for depthFirstSearch
		/// </summary>
		/// <param name="t_deltaTime"></param>
		if (m_switcher == WhichAlgorithm::DEPTH)
		{
			if (temp == false)
			{
				m_depthFirstSearch.computeShortestPath(m_tempstart, m_tempsEnd, &m_grid);
				
			}
			

			if (m_gridSizeState == GridSize::small)
			{


				std::string message = "large";
				std::string depthfirstSearch_Result = std::to_string((m_depthFirstSearch.getTimer().asSeconds()));
				std::ofstream outputData("DepthSmall.csv", std::ios::app);
				outputData << message << depthfirstSearch_Result << std::endl;
				outputData.close();


			}
			else if (m_gridSizeState == GridSize::large)
			{


				std::string message = "large";
				std::string depthfirstSearch_Result = std::to_string((m_depthFirstSearch.getTimer().asSeconds()));
				std::ofstream outputData("DepthMedium.csv", std::ios::app);
				outputData << message << depthfirstSearch_Result << std::endl;
				outputData.close();


			}
			else if (m_gridSizeState == GridSize::veryLarge)
			{


				std::string message = "large";
				std::string depthfirstSearch_Result = std::to_string((m_depthFirstSearch.getTimer().asSeconds()));
				std::ofstream outputData("DepthLarge.csv", std::ios::app);
				outputData << message << depthfirstSearch_Result << std::endl;
				outputData.close();


			}

		}
		/// <summary>
		///  testing for djkstras
		/// </summary>
		/// <param name="t_deltaTime"></param>
		if (m_switcher == WhichAlgorithm::DIKSTRAS)
		{
			if (temp == false)
			{
				m_dijkstras.computeShortestPath(m_tempstart, m_tempsEnd, &m_grid);
				

			}
			


			if (m_gridSizeState == GridSize::small)
			{
				std::string message = "small";
				std::string djkstras = std::to_string((m_dijkstras.getTimer().asSeconds()));
				std::ofstream outputData("djkstrasSmall.csv", std::ios::app);
				outputData << message << djkstras << std::endl;
				outputData.close();

			}
			else if (m_gridSizeState == GridSize::large)
			{

				std::string message = "medium";
				std::string DstarResult = std::to_string((m_dijkstras.getTimer().asSeconds()));
				std::ofstream outputData("djkstrasmedium.csv", std::ios::app);
				outputData << message << DstarResult << std::endl;
				outputData.close();

			}
			else if (m_gridSizeState == GridSize::veryLarge)
			{


				std::string message = "large";
				std::string DstarResult = std::to_string(m_dijkstras.getTimer().asSeconds());
				std::ofstream outputData("djkstraslarge.csv", std::ios::app);
				outputData << message << DstarResult << std::endl;
				outputData.close();


			}

		}
		/// <summary>
		///  play mode for Lpa star
		/// </summary>
		/// <param name="t_deltaTime"></param>
		if (m_switcher == WhichAlgorithm::LPASTAR)
		{
			if (m_LpaStar.getLpaStarPathFound() == false)
			{
				if (temp == false)
				{
					m_LpaStar.LPAStar(m_tempstart, m_tempsEnd, &m_grid);
					
				}
			
				if (m_gridSizeState == GridSize::small)
				{


					std::string message = "SMALL";
					std::string lpaResult = std::to_string((m_LpaStar.getTimer().asSeconds()));
					std::ofstream outputData("LPASmall.csv", std::ios::app);
					outputData << message << lpaResult << std::endl;
					outputData.close();


				}
				else if (m_gridSizeState == GridSize::large)
				{
		
					std::string lpaResult = std::to_string((m_LpaStar.getTimer().asSeconds()));
					std::ofstream outputData("LPAMED.csv", std::ios::app);
					outputData << lpaResult << std::endl;
					outputData.close();
				}

				else if (m_gridSizeState == GridSize::veryLarge)
				{
					std::string lpaResult = std::to_string((m_LpaStar.getTimer().asSeconds()));
					std::ofstream outputData("LPAlargeGrid.csv", std::ios::app);
					outputData << lpaResult << std::endl;
					outputData.close();
				}
			}
		}
		if (m_raceState == Race::yes)
		{

			if (m_tempstartTwo != nullptr)
			{
				if (tempOne == false)
				{
					m_dStarLite.DstarLiteMain(m_tempstartTwo, m_tempsEndTwo, &m_gridTwo);
					tempOne = true;
				}
				
			}
		}
		
	}

		

}


void Game::processEvents()
{
	sf::Event newEvent;
	
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseInput(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	
}

// gets the mouse input on the screen and copies that info to the second
// dstar lite screen
void Game::processMouseInput(sf::Event t_event)
{

	sf::Vector2f m_QMousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };// the  interactable window
	if (m_gridSizeState == GridSize::small || m_gridSizeState == GridSize::large || m_gridSizeState == GridSize::veryLarge)
	{
		//mouse click
		
			if (sf::Mouse::Left == t_event.key.code)
			{
				for (int j = 0; j < m_grid.getNumberOfRows(); j++)
				{
					for (int i = 0; i < m_grid.getnumberOfCols(); i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{
							m_grid.m_theTableVector.at(i).at(j).setStartColour();
							m_grid.m_theTableVector.at(i).at(j).setStartPoint(true);

							
							m_startCelI_Id = m_grid.m_theTableVector.at(i).at(j).getID();
							if (temp == true)
							{
								m_temp = false;
							}
							if (tempOne == true)
							{
								tempOne = false;
							}

							m_SrtChosen = true;

							if (m_raceState == Race::yes)
							{
								m_startCellTwo_Id = m_gridTwo.m_theTableVector.at(i).at(j).getID();
								m_gridTwo.m_theTableVector.at(i).at(j).setStartColour();
								m_gridTwo.m_theTableVector.at(i).at(j).setStartPoint(true);

							}
						}
					}
				}
			
			}
		


		
			if (sf::Mouse::Right == t_event.key.code)
			{
				for (int j = 0; j < m_grid.getNumberOfRows(); j++)
				{
					for (int i = 0; i < m_grid.getnumberOfCols(); i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{
							m_grid.m_theTableVector.at(i).at(j).setEndColour();
							m_grid.m_theTableVector.at(i).at(j).setEndPoint(true);

							

							m_EndCell_Id = m_grid.m_theTableVector.at(i).at(j).getID();
							

							if (m_raceState == Race::yes)
							{
								m_gridTwo.m_theTableVector.at(i).at(j).setEndColour();
								m_gridTwo.m_theTableVector.at(i).at(j).setEndPoint(true);
								m_EndCellTwo_Id = m_gridTwo.m_theTableVector.at(i).at(j).getID();
							}
							m_EndChosen = true;
							if (temp == true)
							{
								m_temp = false;
							}
							if (tempOne == true)
							{
								tempOne = false;
							}
							
							
						}
					}
				}
			}
		


		
			if (sf::Mouse::Middle == t_event.key.code)
			{
				for (int j = 0; j < m_grid.getNumberOfRows(); j++)
				{
					for (int i = 0; i < m_grid.getnumberOfCols(); i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{

							m_grid.m_theTableVector.at(i).at(j).setTraversable(false);
							if (temp == true)
							{
								m_temp = false;
							}
							if (tempOne == true)
							{
								tempOne = false;
							}
							
							if (m_raceState == Race::yes)
							{
								m_gridTwo.m_theTableVector.at(i).at(j).setTraversable(false);
							}
							m_LpaStar.setTerminationCondition(false);
							
						
						}
					}
				}
			}
		
	}
}

// update function checks the status of all enums and changes state of the programe
// from play to testing and vice versa
void Game::update(sf::Time t_deltaTime)
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_mode = Mode::PLAY;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		m_mode = Mode::TESTING;
	}
	
	


		m_gridSizeState = m_menu.setGridSize(m_windowTwo, m_grid, m_gridTwo, m_cellVAR);
		if (m_raceState == Race::No)
		{
			m_raceState = m_menu.getRaceStatus();
		}
		
		
		m_switcher = m_menu.getalg();
	
		if (m_debugState == debug::Off)
		{
			m_debugState = m_menu.getdebugStatus();
		}
		

	
	if (m_mode == Mode::PLAY)
	{
		PlayMode();	
	}
	/// <summary>
	/// this has random start and end position to avoid bias 
	/// </summary>
	/// <param name="t_deltaTime"></param>
	if (m_mode == Mode::TESTING)
	{
		TestingMode();
	
	}

}

// render function for all windows
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_windowTwo.clear(sf::Color::White);
	m_grid.render(m_window);
	if (m_raceState == Race::yes)
	{
		m_gridTwo.render(m_windowAstar);
		if (m_debugState == debug::On)
		{

		
			if (m_gridTwo.getMAXCELLS()==100)
			{
				for (int i = 0; i < m_gridTwo.getMAXCELLS(); i++)
				{
					Cell* v = m_gridTwo.atIndex(i);
					m_windowAstar.draw(v->m_rhsText);
					m_windowAstar.draw(v->m_KeyText);
					m_windowAstar.draw(v->m_GcostText);
				}
			}
		}
	}
	else {
		m_windowTwo.clear(sf::Color::White);
	}
	
	m_menu.render(m_windowTwo);
	
	m_window.display();
	m_windowTwo.display();
	m_windowAstar.display();

}



