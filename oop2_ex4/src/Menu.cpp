#include"Menu.h"

//--------------------------------------------------

Menu::Menu()
{
    // set buttons data
    setUndo();
    setReset();
    setExit();
}
//--------------------------------------------------
// print menu data

void Menu::printGameInfo(sf::RenderWindow& window, int level, int moves) const {
    printLevel(window, level);
    printNumOfMoves(window, moves);
    window.draw(m_resetRect);
    window.draw(m_undoRect);
    window.draw(m_exitRect);
}
//--------------------------------------------------
// set and print num of level data

void Menu::printLevel(sf::RenderWindow& window, int level) const {
    std::ostringstream oss;
    oss << " Level: " << level;
    sf::Text text;
    text.setScale(MENU_SCALE);
    text.setFont(*FileManager::p2FileManager().getFont());
    text.setString(oss.str());
    text.setColor(sf::Color::Black);
    text.setPosition(LEVEL_POS);
    window.draw(text);
}
//--------------------------------------------------
// set and print num of moves data

void Menu::printNumOfMoves(sf::RenderWindow& window, int moves) const{
    std::ostringstream oss;
    oss << "Moves: " << moves;
    sf::Text text;
    text.setScale(MENU_SCALE);
    text.setFont(*FileManager::p2FileManager().getFont());
    text.setString(oss.str());
    text.setColor(sf::Color::Black);
    text.setPosition(MOVES_POS);
    window.draw(text);
}
//--------------------------------------------------
// set reset button

void Menu::setReset() {
    auto resetTexture = FileManager::p2FileManager().getIconTexture(RESET);
    auto rect = sf::RectangleShape(RESET_SIZE);
    rect.setTexture(resetTexture);
    rect.setScale(RESET_SCALE);
    rect.setPosition(RESET_POS);
    m_resetRect = rect;
}
//--------------------------------------------------
// set undo button

void Menu::setUndo() {
    auto undoTexture = FileManager::p2FileManager().getIconTexture(UNDO);
    auto rect = sf::RectangleShape(UNDO_SIZE);
    rect.setTexture(undoTexture);
    rect.setScale(UNDO_SCALE);
    rect.setPosition(UNDO_POS);
    m_undoRect = rect;
}
//--------------------------------------------------
// set exit button

void Menu::setExit() {
    auto exitTexture = FileManager::p2FileManager().getIconTexture(EXIT);
    auto rect = sf::RectangleShape(EXIT_SIZE);
    rect.setTexture(exitTexture);
    rect.setScale(MENU_SCALE);
    rect.setPosition(EXIT_POS);
    m_exitRect = rect;
}
//--------------------------------------------------
// check if reset button pressed

bool Menu::checkreset(const sf::Event::MouseButtonEvent& event) {
    if (m_resetRect.getGlobalBounds().contains(event.x, event.y)) {
        playSounds(S_RESET);
        return true;
    }
    return false;
}
//--------------------------------------------------
// check if undo button pressed

bool Menu::checkundo(const sf::Event::MouseButtonEvent& event) {
    if (m_undoRect.getGlobalBounds().contains(event.x, event.y)) {
        playSounds(S_UNDO);
        return true;
    }
    return false;     
}
//--------------------------------------------------
// check if exit button pressed

bool Menu::checkExit(const sf::Event::MouseButtonEvent& event) const{
    if (m_exitRect.getGlobalBounds().contains(event.x, event.y))
        return true;
    return false;
}
//--------------------------------------------------
// play buttons sounds

void Menu::playSounds(sounds sound) {
    m_buttonSound.setBuffer(*FileManager::p2FileManager().getSound(sound));
    m_buttonSound.play();
}
//--------------------------------------------------
// check if user move the mouse over the buttons

void Menu::handleMove(const sf::Event::MouseMoveEvent& event) {
    checkMove(m_undoRect, event);
    checkMove(m_resetRect, event);
    checkMove(m_exitRect, event);
}
//--------------------------------------------------
// if user move the mouse over the button mark this button

void Menu::checkMove(sf::RectangleShape &button, const sf::Event::MouseMoveEvent& event) {
    if (button.getGlobalBounds().contains(event.x, event.y))
        button.setFillColor(PAINTED_TAIL);
    else
        button.setFillColor(PAINTED_BACK_TAIL);
}