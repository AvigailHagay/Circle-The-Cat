#include"Cat.h"

//--------------------------------------------------

void Cat::setSprite(sf::Sprite sprite) {
    m_sprite = sprite;
    m_sprite.setTextureRect(m_standing_cat);
    m_stack.push(m_sprite);// for the undo button
}
//--------------------------------------------------

void Cat::action(std::vector<std::vector<GameObject>>& board) {
    m_userWon = false;
    m_catWon = false;
    board[m_catRow][m_catCol].setCatIn(false);
    findNextTile(board); // find the shortest path
    m_sprite.setPosition(board[m_catRow][m_catCol].getSprite().getPosition());
    board[m_catRow][m_catCol].setCatIn(true);
    m_stack.push(m_sprite); // push last move
    for (auto& i : m_foundedBy) // reset vector
        memset(&i[0], 0, sizeof(sf::Vector2f) * i.size());
}
//--------------------------------------------------
//return cat to the starting pos

void Cat::returnCatPos(std::vector<std::vector<GameObject>>& board) {
    m_catRow = m_catCol = START_CAT_POS;
    m_sprite.setPosition(board[m_catRow][m_catCol].getSprite().getPosition());
    m_sprite.setTextureRect(m_standing_cat);
    board[m_catRow][m_catCol].setCatIn(true);
    m_stack.push(m_sprite);
}
//--------------------------------------------------

void Cat::print(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}
//--------------------------------------------------
// check whether given cell (row, col) is a valid cell or not.

bool Cat::isValid(int row, int col) const {
    return (row >= 0) && (row < MAX_TILES) &&
        (col >= 0) && (col < MAX_TILES);
}
//--------------------------------------------------
// check whether given cell (row, col) is in the frame

bool Cat::isInFrame(int row, int col) const {
    return (row == MIN_FRAME) || (row == MAX_FRAME) ||
        (col == MIN_FRAME) || (col == MAX_FRAME);
}
//--------------------------------------------------
// find the next hexagon to move the cat on it

void Cat::findNextTile(std::vector<std::vector<GameObject>>& board) {
    bfs(board);
    queueNode min = findMinDis();

    if (min.dist < MAX_TILES * MAX_TILES && min.dist > 0 && !m_random)
        moveCat(min);
    else if (!isInFrame(m_catRow,m_catCol))// if cat not win
        moveRandom(board);
    else {
        m_catWon = true;
        m_random = false;
    }
}
//--------------------------------------------------
// function to find the shortest path from a given source cell

void Cat::bfs(std::vector<std::vector<GameObject>>& board)
{
    bool visited[MAX_TILES][MAX_TILES];
    memset(visited, false, sizeof visited);

    // Create a queue for BFS
    std::queue<queueNode> q;

    // Distance of source cell is 0
    queueNode s = { {(float)m_catRow,(float)m_catCol }, 0 };
    q.push(s);  // Enqueue source cell

    // Do a BFS starting from the cat position
    while (!q.empty())
    {
        queueNode curr = q.front();
        sf::Vector2f pt = curr.pt;
        // If we have reached a cell of the frame, we push it into the queue
        if (isInFrame(pt.x,pt.y))
            m_frame.push(curr);
           
        q.pop();
        // check the 6 sides of the hexagon
        for (int i = 0; i < SIDES; i++) {
            int row = pt.x, col = pt.y;
            chooseRowCol(row, col,i);
            // if adjacent cell is valid, if path and not visited yet, enqueue it
            if (isValid(row, col) && !visited[row][col] && (!board[row][col].getStstus()))
            {
                // mark cell as visited and enqueue it
                visited[row][col] = true;
                queueNode Adjcell = { {(float)row, (float)col}, curr.dist + NEXT_HEX };
                // insert into the m_foundedBy vector- who found me
                m_foundedBy[row][col] = { (float)curr.pt.x,(float)curr.pt.y };
                q.push(Adjcell);
            } 
        }
    }
}
//--------------------------------------------------
// choose 6 sides by the oddity

void Cat::chooseRowCol(int& row, int& col, int index) const {
    if (row % EVEN_ROWS == 0) {
        row += ROW_NUM_EVEN[index];
        col += COL_NUM_EVEN[index];
    }
    else {
        row += ROW_NUM_ODD[index];
        col += COL_NUM_ODD[index];
    }
}
//--------------------------------------------------
//find the minimum dis from frame to the cat

queueNode Cat::findMinDis() {
    int minDis = MAX_TILES * MAX_TILES;
    queueNode min;
    min.dist = minDis;
    while (m_frame.size() > 1) {
        if (m_frame.front().dist < minDis) {
            minDis = m_frame.front().dist;
            min = m_frame.front();
        }
        m_frame.pop();
    }
    return min;
}

//--------------------------------------------------
//move the cat to the first move in the shortest path

void Cat::moveCat(queueNode min) {
 
    sf::Vector2f point = { min.pt.x,min.pt.y };
    while ((!(m_foundedBy[point.x][point.y].x == m_catRow && m_foundedBy[point.x][point.y].y == m_catCol)))
        point = m_foundedBy[point.x][point.y];
        
    updateAnimation(m_catRow, m_catCol, point.x, point.y);
    m_catRow = point.x;
    m_catCol = point.y;      
}
//--------------------------------------------------
// after the cat has no path to the frame- then move random

void Cat::moveRandom(std::vector<std::vector<GameObject>> board) {
    m_random = true;
    while (true) {
        sf::Vector2f dir = grillDirection();
        if (!board[m_catRow + dir.x][m_catCol + dir.y].getStstus() && 
            !board[m_catRow + dir.x][m_catCol + dir.y].getIsCatIn()) {
            m_catRow += dir.x;
            m_catCol += dir.y;
            updateAnimation(m_catRow - dir.x, m_catCol - dir.y, m_catRow, m_catCol);
            break;
        }
        // if the cat has no avalible hexagon to go
        if (!noAvalibleCells(board)) {
            m_random = false;
            m_userWon = true;
            break;
        }
    }
}
//--------------------------------------------------
// grill random dir between 6 sides

sf::Vector2f Cat::grillDirection() const {
    int dir = rand() % SIDES;
    if (m_catRow % EVEN_ROWS == 0)
        return{ (float)ROW_NUM_EVEN[dir], (float)COL_NUM_EVEN[dir] };
    else
        return{ (float)ROW_NUM_ODD[dir], (float)COL_NUM_ODD[dir] };
}
//--------------------------------------------------
// check if all 6 sides of the cat isnt avalible

bool Cat::noAvalibleCells(std::vector<std::vector<GameObject>> board) const {
    for (int i = 0; i < SIDES; i++) {
        if (m_catRow % EVEN_ROWS == 0) {
            if (!board[m_catRow + ROW_NUM_EVEN[i]][m_catCol + COL_NUM_EVEN[i]].getStstus())
                return true;
        }
        else
            if (!board[m_catRow + ROW_NUM_ODD[i]][m_catCol + COL_NUM_ODD[i]].getStstus())
                return true;
    }
    return false;
}
//--------------------------------------------------
// update animation by the side

void Cat::updateAnimation(int prvRow, int prvCol, int currRow, int currCol) {
    int rowAnimation = MIDDLE, colAnimation = LEFT;

    if (prvRow < currRow)
        rowAnimation = RIGHT;
    if (prvRow > currRow)
        rowAnimation = LEFT;
    colAnimation = chooseColByOddity(prvRow, prvCol, currCol);
    if (prvCol > currCol && rowAnimation == MIDDLE)
        colAnimation = LEFT;
    if (prvCol < currCol && rowAnimation == MIDDLE)
        colAnimation = RIGHT;

    sf::IntRect i(colAnimation * IMAGE_WIDTH, rowAnimation * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
    m_sprite.setTextureRect(i);
}
//--------------------------------------------------

int Cat::chooseColByOddity(int prvRow, int prvCol, int currCol) const {
    if (prvRow % EVEN_ROWS == 0) 
        if (prvCol == currCol)
            return RIGHT;
        else
            return LEFT;
    else if (!prvRow % EVEN_ROWS == 0)
        if (prvCol == currCol)
            return LEFT;
        else
            return RIGHT;
}
//--------------------------------------------------
// undo the last move of the cat

void Cat::undo(std::vector<std::vector<GameObject>>& board) {
    if (m_stack.size() > FIRST_POS) {
        board[m_catRow][m_catCol].setCatIn(false);
        m_stack.pop();
        m_sprite = m_stack.top();
        changeCatRowCol(board);
        board[m_catRow][m_catCol].setCatIn(true);
    } 
}
//--------------------------------------------------
// set cat pos after the undo 

void Cat::changeCatRowCol(std::vector<std::vector<GameObject>>& board) {
    for(int i = 0; i < MAX_TILES; i++)
        for(int j = 0; j < MAX_TILES; j++)
            if (board[i][j].getSprite().getGlobalBounds().contains(m_stack.top().getPosition())) {
                m_catRow = i;
                m_catCol = j;
            }
    m_random = false;//so it wont move random
}
//--------------------------------------------------

void Cat::clearStack() {
    while (!m_stack.empty())
        m_stack.pop();
}
