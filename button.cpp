#include "button.hpp"

sf::Text* buie::Button::label()
{
	return &(buie::Button::buttonLabel);
}

void buie::Button::updateLabelPosition()
{
	sf::Vector2f(buie::Button::getPosition().x - buie::Button::getSize().x / 2.0, buie::Button::getPosition().y - buie::Button::getSize().y / 2.0);
}