#include "Controller.h"

//--------------------------------------------------

Controller::Controller() 
	: m_window(sf::VideoMode(COL_SIZE_OF_WINDOW, ROW_SIZE_OF_WINDOW), "Circle The Cat")
{
	m_runLevel.openingScreen(m_window);
	setLevel();
	m_runLevel.updateBoard();
}
//--------------------------------------------------

void Controller::run(){
	
	while (m_window.isOpen()) {
		checkAndUpdateLevel();// check if next level, win or lose
		m_window.clear(sf::Color().White);
		m_runLevel.printBoard(m_window);
		m_menu.printGameInfo(m_window, m_levelNumber, m_moves);
		handleEvents();
		m_window.display();
		if (m_exit)
			break;
	}
}
//--------------------------------------------------

void Controller::checkAndUpdateLevel() {
	if (m_runLevel.getEndLevel() || m_levelNumber == 0 || m_runLevel.getRunAgain()) {
		if (m_runLevel.getRunAgain()) {
			m_levelNumber--;
			m_runLevel.setRunAgain(false);
		}
		m_moves = 0;// reset num of moves
		m_levelNumber++;
		m_runLevel.updateLevel(m_levels[m_levelNumber - 1], m_levelNumber);// update board
		m_runLevel.setEndLevel(false);
	}	
}
//--------------------------------------------------

void Controller::handleEvents(){
	for (auto event = sf::Event{}; m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseMoved:
			// handle buttons
			m_menu.handleMove(event.mouseMove);
			// handle hexagaons
			m_runLevel.handleMove(m_window, event.mouseMove);
			break;
		case sf::Event::MouseButtonReleased:
			// check if buttons pressed
			checkButtons(event);
			m_runLevel.handleRound(event.mouseButton, m_moves, m_window);
			break;
		}
	}
}
//--------------------------------------------------

void Controller::checkButtons(const sf::Event& event) {
	if (m_menu.checkreset(event.mouseButton))
		reset();
	if (m_menu.checkundo(event.mouseButton))
		m_runLevel.undo(m_moves);
	if(m_menu.checkExit(event.mouseButton))
		m_exit=true;
}
//--------------------------------------------------

void Controller::reset() {
	m_levels.clear();
	m_moves = 0;// reset num of moves
	setLevel();// create 3 levels
	m_runLevel.updateLevel(m_levels[m_levelNumber - 1], m_levelNumber);
}
//--------------------------------------------------

void Controller::setLevel() {
	srand(time(0));
	for (int i = 0; i < MAX_LEVEL; i++) {
		m_levels.push_back(createNewLevel(i));// // create 3 levels
	}
}
//--------------------------------------------------

std::vector < sf::Vector2f>Controller::createNewLevel(const int level) {
	std::vector < sf::Vector2f> levelInfo;// contain the marked hexagon of each level
	for (int i = 0; i < MAX_PRINTED / (level + 1); i++) {
		//grill the marked hexagon
		int a = rand() % ((RANGE_LEVEL + level) + 1 - (MAX_LEVEL - level)) + (MAX_LEVEL - level);
		int b = rand() % ((RANGE_LEVEL + level) + 1 - (MAX_LEVEL - level)) + (MAX_LEVEL - level);
		//so the marked hexagon wont be on the cat position 
		//and on other marked hexagon
		if (a == START_CAT_POS && b == START_CAT_POS || !uniquePt(a, b, levelInfo))
			i--;
		else
			levelInfo.push_back(sf::Vector2f(a, b));
	}
	return levelInfo;
}
//--------------------------------------------------

bool Controller::uniquePt(int a, int b, std::vector < sf::Vector2f>vec) const {
	for (auto& i : vec)
		if (i.x == a && i.y == b)
			return false;
	return true;
}