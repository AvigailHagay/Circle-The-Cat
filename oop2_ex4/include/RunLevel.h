#pragma once

#include "GameObject.h"
#include"User.h"
#include"Cat.h"
#include <vector>
#include <chrono>
#include <thread>

class RunLevel
{
public:
	RunLevel() {};
	~RunLevel() {};
	void openingScreen(sf::RenderWindow& window) const;
	void updateBoard();
	void printBoard(sf::RenderWindow& window) const;
	void handleMove(sf::RenderWindow& m_window, const sf::Event::MouseMoveEvent& event);
	void handleRound(const sf::Event::MouseButtonEvent& event, int& moves, sf::RenderWindow& window);
	void undo(int& moves);
	void updateLevel(std::vector<sf::Vector2f>level, int numLevel);
	bool getEndLevel()const { return m_endLevel; }
	bool getRunAgain()const { return m_runAgain; }
	void setRunAgain(bool again) { m_runAgain = again; }
	void setEndLevel(bool level) { m_endLevel = level; }

private:
	void setCatData();
	void setWinLossScreen(backgroundsType backgroundType, sounds soundType, 
		sf::RenderWindow& window) const;
	void chooseColPos(bool& even, double& posCol) const;
	sf::RectangleShape initializeRect() const;

	std::vector<std::vector<GameObject>> m_board;
	sf::Sprite m_catSprite;
	sf::Sprite m_hexagon;
	sf::Music m_winSound;
	User m_user;
	Cat m_cat;
	int m_numLevel = 0;
	bool m_endLevel = false;
	bool m_runAgain = false;
};