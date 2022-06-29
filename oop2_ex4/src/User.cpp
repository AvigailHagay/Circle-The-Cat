#include"User.h"

//--------------------------------------------------

User::User() {
    m_clickSound.setBuffer(*FileManager::p2FileManager().getSound(S_CLICK));
}
//--------------------------------------------------

bool User::action(const sf::Event::MouseButtonEvent& event,
    std::vector<std::vector<GameObject>>& board, int& moves) {

    for (auto& i : board)
        for (auto& j : i)
            if (j.getRec().getGlobalBounds().contains(event.x, event.y)) {
                //if hexagon pressed
                if (!j.getStstus() && !j.getIsCatIn()) {
                    m_clickSound.play(); // play click sound
                    j.paintTail(); // mark the hexagon
                    moves++;
                    j.setStatus(true);
                    // push the pressed hexagon into stack(for the undo button)
                    m_stack.push(j); 
                    return true;
                }
            }
    return false;
}
//--------------------------------------------------

void User::undo(std::vector<std::vector<GameObject>>& board, int& moves) {
    // undo last move
    if (!m_stack.empty()) {
        for (auto& i : board)
            for (auto& j : i)
                if (m_stack.top() == j) {
                    j.paintBackTail();
                    j.setStatus(false);//set hexagon as not pressed yet
                    moves--;
                }     
        m_stack.pop();
    }
}
//--------------------------------------------------

void User::clearStack() {
    while (!m_stack.empty())
        m_stack.pop();
}