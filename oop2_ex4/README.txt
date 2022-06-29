1.Circle the cat
2.Avigail Hagay & Lior Ezra (318201688,208589762)

3.
A user VS computer game. The player in his turn selects one tile he wants to block by clicking on it
The computer in its turn moves the cat to try to escape obstacles, and to escape from the board. 
If the cat reached one side of the board, the cat actually ran away from the board and won the game. 
If the player succeeded surround the cat on all sides, as mentioned, the player won. 

4.
Controller - run the game
RunLevel - run the level	
FileManager - a singletone class, contain all the sounds, icons, fonts and backgrounds 
GameObject - a class that manage all the tiles of the board
Menu - a class that manage all the menu data
Cat - conatin all cat data- pos, sprite, and more
User - conatin all user data

5.
"Marcos.h"- contain all the const and the enum data
"Controller.h"-The Controller's class in this file we will hold the public functions and the private members
"RunLevel.h"-The RunLevel's class in this file we will hold the public functions and the private members
"FileManager.h"-The FileManager's class in this file we will hold the public functions and the private members
"GameObject.h"-The GameObject's class in this file we will hold the public functions and the private members
"Menu.h"-The Menu's class in this file we will hold the public functions and the private members
"Cat.h"-The Cat's class in this file we will hold the public functions and the private members
"User.h"-The User's class in this file we will hold the public functions and the private members

"Controller.cpp"- contain all the functions that run the game
"RunLevel.cpp"- contain all the functions that run the level
"FileManager.cpp"- contain all the functions that set the sounds, icons, fonts and backgrounds
"GameObject.cpp"- contain all the function of the tiles
"Menu.cpp"- contain all the function of the menu data
"Cat.cpp"- contain all the function of the cat- move, bfs, animation and more
"User.cpp"- contain all the function of the user- click handle, undo and more

6.
std::stack<sf::Sprite>m_stack - contain the all last moves of the cat, we undo the last move by pop-O(1) 
std::stack<GameObject>m_stack - contain the all last moves of the User, we undo the last move by pop-O(1)
std::vector<std::vector<sf::Vector2f>>m_foundedBy - a matrix that contain in its cell which point found the curr point-
so we know the first move of the shortest path
std::vector<std::vector<sf::Vector2f>>m_levels - contain the 3 boards of each level
std::queue<queueNode> q - for the bfs algorithm

7.
used the bfs algrithm for the shotest path between the cat and the frame of the board,
then we keep the 40 pathes in a queue, and check for the min path in the queue
8.
9.
we made a singlton class so we load the sounds, fonts and images only once





											  
