#include "textField.hpp"

void buie::TextField::setEmptyPlaceholderMode(const bool option)
{
	if ((buie::TextField::hidePlaceholderWhenSelected = option) == false)
	{
		if (buie::TextField::label()->getString() == "")
			buie::TextField::label()->setString(buie::TextField::emptyFieldPlaceholder);
		return;
	}
	if ((buie::TextField::isPressed() == true) && (buie::TextField::label()->getString() == buie::TextField::emptyFieldPlaceholder))
	{
		buie::TextField::label()->setString("");
	}
}

bool buie::TextField::getEmptyPlaceholderMode() const
{
	return buie::TextField::hidePlaceholderWhenSelected;
}

void buie::TextField::setEmptyPlaceholder(const sf::String& placeholder)
{
	if (buie::TextField::label()->getString() == buie::TextField::emptyFieldPlaceholder)
	{
		buie::TextField::label()->setString(placeholder);
	}
	buie::TextField::emptyFieldPlaceholder = placeholder;
}

sf::String buie::TextField::getInput()
{
	return buie::TextField::label()->getString();
}

void buie::TextField::reset()
{
	buie::TextField::label()->setString(buie::TextField::emptyFieldPlaceholder);
	buie::TextField::selected = false;
}

bool buie::TextField::isSelected() const
{
	return buie::TextField::selected;
}

void buie::TextField::onEvent(const sf::Vector2f& pointerPos, const sf::Event& event)
{
	if (buie::TextField::isPressed(pointerPos, event.type) == true)
	{
		buie::TextField::selected = true;
	}
	else
	{
		buie::TextField::selected = false;
	}

	if (buie::TextField::selected == true)
	{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == 8)
				buie::TextField::label()->setString(buie::TextField::label()->getString().substring(0, buie::TextField::label()->getString().getSize() - 1));
			else
				buie::TextField::label()->setString(buie::TextField::label()->getString() + event.text.unicode);
		}
	}
}
