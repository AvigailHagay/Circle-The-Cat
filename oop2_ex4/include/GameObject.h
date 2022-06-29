#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <stack>
#include <algorithm>
#include <iterator>
#include"FileManager.h"

class GameObject
{
public:
	GameObject(bool status, sf::Sprite sprite, sf::RectangleShape rect);
	GameObject() {};

	void print(sf::RenderWindow& window) const;
	void paintTail();
	void paintBackTail();
	void markTail();
	void setStatus(bool status) { m_status = status; }
	void setCatIn(bool catIn) { m_cat_in = catIn; }
	void setSprite(sf::Sprite sprite) { m_sprite = sprite; }
	void setRec(sf::RectangleShape rec) { m_rect = rec; }

	bool getStstus() const { return m_status; }
	bool getIsCatIn() const { return m_cat_in; }
	sf::RectangleShape getRec()const { return m_rect; }
	sf::Sprite& getSprite() { return m_sprite; }
	
	bool operator==(const GameObject& obj) const;
private:

	bool m_cat_in = false;
	bool m_status = false;
	sf::Sprite m_sprite;
	sf::RectangleShape m_rect;
};