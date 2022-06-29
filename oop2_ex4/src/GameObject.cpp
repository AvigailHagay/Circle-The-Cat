#include "GameObject.h"

//--------------------------------------------------

GameObject::GameObject(bool status, sf::Sprite sprite, sf::RectangleShape rect)
	:m_status(status), m_sprite(sprite), m_rect(rect)
{
	m_rect.setTexture(sprite.getTexture());
}
//--------------------------------------------------

void GameObject::print(sf::RenderWindow& window) const{
	window.draw(m_sprite);
}
//--------------------------------------------------

void GameObject::paintTail() {
	m_sprite.setColor(PAINTED_TAIL);
}
//--------------------------------------------------

void GameObject::paintBackTail() {
	m_sprite.setColor(PAINTED_BACK_TAIL);
}
//--------------------------------------------------

void GameObject::markTail() {
	m_sprite.setColor(MARK_TAIL);
}
//--------------------------------------------------
bool GameObject::operator==(const GameObject& obj) const {
	return m_rect.getPosition() == obj.getRec().getPosition();
}
