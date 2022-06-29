#pragma once

#include"SFML/Graphics.hpp"
#include"RunLevel.h"
#include <sstream>
#include <iostream>

class Menu
{
public:
	Menu();
	~Menu() {};
	bool checkundo(const sf::Event::MouseButtonEvent& event);
	bool checkreset(const sf::Event::MouseButtonEvent& event);
	bool checkExit(const sf::Event::MouseButtonEvent& event) const;
	void printGameInfo(sf::RenderWindow& window, int level, int moves) const;
	void handleMove(const sf::Event::MouseMoveEvent& event);

private:
	void checkMove(sf::RectangleShape& button, const sf::Event::MouseMoveEvent& event);
	void printLevel(sf::RenderWindow& window, int level) const;
	void printNumOfMoves(sf::RenderWindow& window, int level) const;
	void playSounds(sounds sound);
	void setUndo();
	void setReset();
	void setExit();
	
	int m_level;
	sf::Sound m_buttonSound;
	sf::RectangleShape m_resetRect;
	sf::RectangleShape m_undoRect;
	sf::RectangleShape m_exitRect;
};