#pragma once

#include"RunLevel.h"
#include"GameObject.h"
#include"User.h"
#include"Menu.h"
#include<vector>
#include <time.h>

class Controller
{
public:
	Controller();
	void run();

private:
	void handleEvents();
	void setLevel();
	void reset();
	void checkButtons(const sf::Event& event);
	void checkAndUpdateLevel();
	void setExit(bool exit) { m_exit = exit; }
	std::vector < sf::Vector2f>createNewLevel(const int level);
	bool uniquePt(int a, int b, std::vector < sf::Vector2f>vec) const;

	RunLevel m_runLevel;
	Menu m_menu;
	sf::RenderWindow m_window;
	int m_levelNumber = 0;
	int m_moves = 0;
	bool m_exit = false;
	std::vector<std::vector<sf::Vector2f>>m_levels;
};