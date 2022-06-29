#pragma once
#include <SFML/Graphics.hpp>
#include"GameObject.h"
#include <queue>

// A Data Structure for queue used in BFS
struct queueNode
{
	sf::Vector2f pt;  // The coordinates of a cell
	int dist;  // cell's distance of from the source

};
class Cat
{
public:
	Cat() {};
	~Cat() {};

	void clearStack();
	void print(sf::RenderWindow& window) const;
	void undo(std::vector<std::vector<GameObject>>& board);
	void action(std::vector<std::vector<GameObject>>& board);
	void returnCatPos(std::vector<std::vector<GameObject>>& board);
	void setSprite(sf::Sprite sprite); 

	sf::Sprite& getSprite() { return m_sprite; }
	bool getIfUserWon()const { return m_userWon; }
	bool getIfCatWon()const { return m_catWon; }
	

private:
	sf::Sprite m_sprite;
	std::queue<queueNode> m_frame;
	int m_catRow = START_CAT_POS;
	int m_catCol = START_CAT_POS;
	bool m_userWon = false;
	bool m_catWon = false;
	bool m_random = false;
	std::stack<sf::Sprite>m_stack;
	std::vector<std::vector<sf::Vector2f>>m_foundedBy{ MAX_TILES, std::vector<sf::Vector2f>(MAX_TILES,{0,0}) };
	sf::IntRect m_standing_cat = { IMAGE_WIDTH, IMAGE_HEIGHT,IMAGE_WIDTH, IMAGE_HEIGHT };

	void bfs(std::vector<std::vector<GameObject>>& board);
	void chooseRowCol(int &row, int &col, int index) const;
	void moveCat(queueNode min);
	void changeCatRowCol(std::vector<std::vector<GameObject>>& board);
	void findNextTile(std::vector<std::vector<GameObject>>& board);
	void updateAnimation(int prvRow, int prvCol, int currRow, int currCol);
	void moveRandom(std::vector<std::vector<GameObject>> board);
	int chooseColByOddity(int prvRow, int prvCol, int currCol) const;
	bool isValid(int row, int col) const;
	bool isInFrame(int row, int col) const;
	bool noAvalibleCells(std::vector<std::vector<GameObject>> board) const;
	sf::Vector2f grillDirection() const;
	queueNode findMinDis();

};