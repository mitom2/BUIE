#include "clickable.hpp"

bool buie::Clickable::isPressed() const
{
	return buie::Clickable::objectPressed;
}

bool buie::Clickable::isPressed(const sf::Vector2f& pointerPos, const sf::Event::EventType& event)
{
	if (event != sf::Event::MouseButtonPressed)
		return false;
	return buie::Clickable::objectPressed = buie::Clickable::getGlobalBounds().contains(pointerPos);
}

bool buie::Clickable::isReleased(const sf::Vector2f& pointerPos, const sf::Event::EventType& event)
{
	if (event != sf::Event::MouseButtonReleased)
		return false;
	return !(buie::Clickable::objectPressed = !(buie::Clickable::getGlobalBounds().contains(pointerPos)));
}

bool buie::Clickable::isHovered(const sf::Vector2f& pointerPos) const
{
	return buie::Clickable::getGlobalBounds().contains(pointerPos);
}