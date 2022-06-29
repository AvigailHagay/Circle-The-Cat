#include "RunLevel.h"

//--------------------------------------------------
void RunLevel::openingScreen(sf::RenderWindow& window) const{
    setWinLossScreen(OPENING, S_OPENING, window);
}
//--------------------------------------------------
// set the all board

void RunLevel::updateBoard() {
    bool even = true;// for the diff between an odd row to even row
    auto hexagon = FileManager::p2FileManager().getIconTexture(HEXAGON);
    m_hexagon.setTexture(*hexagon);
    sf::RectangleShape rect = initializeRect();
    m_hexagon.setScale(HEX_SCALE);
    double posCol, posRow = START_POS_ROW;

    for (int i = 0; i < MAX_TILES; i++) {
        chooseColPos(even, posCol); // choose pos by the oddity of the row
        std::vector<GameObject> row;
        for (int j = 0; j < MAX_TILES; j++) {
            m_hexagon.setPosition((float)(((j * WHIDTH_HEX) + posCol) + HEX_H), 
                (float)(((i * HEIGHT_HEX) + posRow + HEX_W)));
            rect.setPosition(m_hexagon.getPosition());
            GameObject gameObj(false, m_hexagon, rect);
            row.push_back(gameObj);
            posCol += SPACE;
        }
        m_board.push_back(row);
        posRow += SPACE;
    }
    setCatData();
}
//--------------------------------------------------
// the hexagon rect

sf::RectangleShape RunLevel::initializeRect() const{
    auto rect = sf::RectangleShape(sf::Vector2f((float)(WHIDTH_HEX), (float)HEIGHT_HEX));
    rect.setTexture(m_hexagon.getTexture());
    return rect;
}
//--------------------------------------------------
// choose pos by the oddity of the row

void RunLevel::chooseColPos(bool& even, double& posCol) const{
    if (even) {
        posCol = POS_COL;
        even = false;
    }
    else {
        posCol = POS_ROW + WHIDTH_HEX / 2; //POS_ROW;
        even = true;
    }
}
//--------------------------------------------------

void RunLevel::setCatData() {
    auto catTexture = FileManager::p2FileManager().getIconTexture(CAT);
    m_catSprite.setTexture(*catTexture);
    m_catSprite.setPosition(m_board[START_CAT_POS][START_CAT_POS].getSprite().getPosition());
    m_catSprite.setScale(CAT_SCALE);
    m_board[START_CAT_POS][START_CAT_POS].setCatIn(true);
    m_cat.setSprite(m_catSprite);
}
//--------------------------------------------------

void RunLevel::printBoard(sf::RenderWindow& window) const{
    for (auto& i : m_board)
        for (auto& j : i)
            j.print(window);
    m_cat.print(window);
}
//--------------------------------------------------
// a generic function that print background and play sound of event

void RunLevel::setWinLossScreen(backgroundsType backgroundType, sounds soundType, 
    sf::RenderWindow& window)const {

    sf::Sound sounds;
    sounds.setBuffer(*FileManager::p2FileManager().getSound(soundType));
    sounds.play();

    sf::RectangleShape background;
    background.setSize({ COL_SIZE_OF_WINDOW, ROW_SIZE_OF_WINDOW });
    background.setTexture(FileManager::p2FileManager().getBackGround(backgroundType));

    window.clear(sf::Color::White);
    window.draw(background);
    window.display();
    Sleep(3000);//sleep 3 sec
}
//--------------------------------------------------

void RunLevel::handleRound(const sf::Event::MouseButtonEvent& event, 
    int& moves, sf::RenderWindow& window) {

    if (!m_user.action(event, m_board, moves)) return; //if user pressed anavilable hex
    m_cat.action(m_board);
    if (m_cat.getIfUserWon() && m_numLevel == MAX_LEVEL) {// if user won level 3
        setWinLossScreen(WON, S_WIN, window);
        exit(EXIT_SUCCESS);
    }
    else if (m_cat.getIfUserWon()) {// if user won a level
        setWinLossScreen(NEXT, S_WIN, window);
        m_endLevel = true;
    }
    else if (m_cat.getIfCatWon()) {
        setWinLossScreen(LOSS, S_LOSS, window);
        m_runAgain = true;
    }
}
//--------------------------------------------------

void RunLevel::updateLevel(std::vector<sf::Vector2f>level ,int numLevel) {
    m_numLevel = numLevel;
    // reset all data
    for (auto& i : m_board)
        for (auto& j : i) {
            j.setStatus(false);
            j.setCatIn(false);
            j.paintBackTail();
        }
    // paint the random tails
    for (auto& i : level) {
        m_board[i.x][i.y].setStatus(true);
        m_board[i.x][i.y].paintTail();
    }
    //clear all the last moves
    m_cat.clearStack();
    m_user.clearStack();
    m_cat.returnCatPos(m_board);
}
//--------------------------------------------------
// if user move the mouse over the tail mark this tail

void RunLevel::handleMove(sf::RenderWindow& m_window, 
    const sf::Event::MouseMoveEvent& event) {
    for (auto& i : m_board)
        for (auto& j : i) {
            if (j.getRec().getGlobalBounds().contains(event.x, event.y) && !j.getStstus() && !j.getIsCatIn())
                j.markTail();
            else if(!j.getStstus() && !j.getIsCatIn())
                j.paintBackTail();
        }
}
//--------------------------------------------------
// handle undo button

void RunLevel::undo(int& moves) {
    m_cat.undo(m_board);
    m_user.undo(m_board , moves);
}