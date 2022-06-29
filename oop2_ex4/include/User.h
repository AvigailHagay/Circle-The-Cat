#pragma once

#include"GameObject.h"

class User
{
public:
    User();
    ~User() {};
    void undo(std::vector<std::vector<GameObject>>& board, int& moves);
    bool action(const sf::Event::MouseButtonEvent& event,
        std::vector<std::vector<GameObject>>& board, int& moves);
    void clearStack();
private:
    sf::Sound m_clickSound;
    std::stack< GameObject > m_stack;
};