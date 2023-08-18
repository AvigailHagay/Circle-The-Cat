#pragma once
#include <SFML/Graphics.hpp>

// general data
const unsigned int NUM_OF_BACKGROUNDS = 4;
const unsigned int NUM_OF_SOUNDS = 6;
const unsigned int NUM_OF_ICONS = 5;

// window data
const int COL_SIZE_OF_WINDOW = 900;
const int ROW_SIZE_OF_WINDOW = COL_SIZE_OF_WINDOW / 1.5;

// controller data
const unsigned int MAX_LEVEL = 3;
const unsigned int RANGE_LEVEL = 8;
const unsigned int MAX_PRINTED = 14;

// gameObject data
const sf::Color MARK_TAIL = { 190, 190, 190, 255 };
const sf::Color PAINTED_TAIL = { 200, 200, 200, 80 };
const sf::Color PAINTED_BACK_TAIL = { 255, 255, 255, 255 };

// cat data
const unsigned int FIRST_POS = 1;
const unsigned int NEXT_HEX = 1;
const unsigned int LEFT = 0;
const unsigned int MIDDLE = 1;
const unsigned int RIGHT = 2;
const unsigned int EVEN_ROWS = 2;
const unsigned int START_CAT_POS = 5;
const unsigned int SIDES = 6;
const unsigned int MAX_TILES = 11;
const unsigned int MAX_FRAME = 10;
const unsigned int MIN_FRAME = 0;
const unsigned int IMAGE_SIZE = 60;
const unsigned int IMAGE_WIDTH = 177;
const unsigned int IMAGE_HEIGHT = 119;

// direction data
const int ROW_NUM_EVEN[] = { -1,-1 ,0 ,0 ,1 ,1 };
const int COL_NUM_EVEN[] = { 0, -1, -1, 1, 0 ,-1 };
const int ROW_NUM_ODD[] = { -1, -1, 0, 0, 1, 1 };
const int COL_NUM_ODD[] = { 0, 1, -1, 1, 0, 1 };

// run_level data
const float HEX_H = COL_SIZE_OF_WINDOW / 3.5;
const float HEX_W = IMAGE_SIZE / 2;
const double START_POS_ROW = 0.25;
const double POS_COL = 8.75;
const double POS_ROW = 9.5;
const double SPACE = 0.5;
const double WHIDTH_HEX = (double)(COL_SIZE_OF_WINDOW - (COL_SIZE_OF_WINDOW / 3.3) - IMAGE_SIZE) / (double)MAX_TILES;//set whidth
const double HEIGHT_HEX = (double)(ROW_SIZE_OF_WINDOW - IMAGE_SIZE) / (double)MAX_TILES;//set height 
const sf::Vector2f HEX_SCALE = { (float)(WHIDTH_HEX) / IMAGE_SIZE, (float)HEIGHT_HEX / IMAGE_SIZE };
const sf::Vector2f CAT_SCALE = { ((double)(COL_SIZE_OF_WINDOW - (COL_SIZE_OF_WINDOW / 3.3) - 60) / (double)MAX_TILES) / 177, ((double)(ROW_SIZE_OF_WINDOW - 60) / (double)MAX_TILES) / 119 };

// menu data
const float MENU_POS = COL_SIZE_OF_WINDOW - (COL_SIZE_OF_WINDOW / 1.10);
const sf::Vector2f MENU_SCALE = { COL_SIZE_OF_WINDOW / 630, ROW_SIZE_OF_WINDOW / 420 };
const sf::Vector2f EXIT_POS = { 0,0 };
const sf::Vector2f RESET_POS = { MENU_POS, ROW_SIZE_OF_WINDOW / 1.4 };
const sf::Vector2f UNDO_POS = { COL_SIZE_OF_WINDOW / 8, ROW_SIZE_OF_WINDOW / 1.75 };
const sf::Vector2f UNDO_SCALE = { (float)(WHIDTH_HEX) / (float)(512/ 0.7), (float)(WHIDTH_HEX) / (float)(512 / 0.7) };
const sf::Vector2f RESET_SCALE = { (float)(WHIDTH_HEX) / (float)(386/ 1.8), (float)HEIGHT_HEX / (float)(386/ 1.8) };
const sf::Vector2f RESET_SIZE = { 530, 386 };
const sf::Vector2f MOVES_POS = { MENU_POS, ROW_SIZE_OF_WINDOW / 2.75 };
const sf::Vector2f LEVEL_POS = { MENU_POS, ROW_SIZE_OF_WINDOW / 6 };
const sf::Vector2f EXIT_SIZE = { 35,35 };
const sf::Vector2f UNDO_SIZE = { 512,512 };
enum icons
{
	HEXAGON, CAT, EXIT, RESET, UNDO
};

enum sounds
{
	S_OPENING, S_WIN, S_LOSS, S_CLICK, S_RESET, S_UNDO
};

enum backgroundsType
{
	OPENING, WON, LOSS, NEXT
};

