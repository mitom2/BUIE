#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "clickable.hpp"

namespace buie
{
	/// @brief Clickable button with a text label.
	/// Buttons should not be rotated.
	class Button : public buie::Clickable
	{

		/// @brief Label of the button.
		sf::Text buttonLabel;

	public:

		/// @brief Get pointer to the button's label.
		/// @return Pointer to label
		sf::Text* label();

		/// @brief Recalculate label position.
		/// This methid should be called everytime the button's coordinates are modified. It will assume upper-left corner of text is the origin point and center the label inside the button.
		/// Label poision relative to the button can be modified throug it's origin point.
		void updateLabelPosition();

	};

}