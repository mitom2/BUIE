#include "animatedButton.hpp"

buie::animated::Button::Button()
{
	buie::animated::Button::pressAnimation = buie::animated::Animation();
}

buie::animated::Button::Button(const Animation& animation)
{
	buie::animated::Button::pressAnimation = buie::animated::Animation(animation);
}

void buie::animated::Button::setAnimation(const buie::animated::Animation& animation)
{
	buie::animated::Button::pressAnimation = buie::animated::Animation(animation);
}

buie::animated::Animation* buie::animated::Button::getAnimationPtr()
{
	return &(buie::animated::Button::pressAnimation);
}

bool buie::animated::Button::isPressed(const double fps)
{
	if (buie::Button::isPressed() == true)
	{
		if (buie::animated::Button::pressAnimation.isLastFrame() == false)
			buie::animated::Button::pressAnimation.animate(fps, buie::animated::Button::buttonAnimatedTexture);
		return true;
	}
	if (buie::animated::Button::pressAnimation.isFirstFrame() == false)
		buie::animated::Button::pressAnimation.animate(fps, buie::animated::Button::buttonAnimatedTexture);
	return false;
}

bool buie::animated::Button::isPressed(const sf::Vector2f& pointerPos, const sf::Event::EventType& event)
{
	if (buie::Clickable::isPressed(pointerPos, event) == true)
	{
		buie::animated::Button::pressAnimation.setOrder(true);
		return true;
	}
	return false;
}

bool buie::animated::Button::isReleased(const sf::Vector2f& pointerPos, const sf::Event::EventType& event)
{
	if (buie::Clickable::isReleased(pointerPos, event) == true)
	{
		buie::animated::Button::pressAnimation.setOrder(false);
		return true;
	}
	return false;
}