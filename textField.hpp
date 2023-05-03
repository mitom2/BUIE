#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "button.hpp"

namespace buie
{

	/// @brief A very simple container for enetering text.
	/// TextField can also behave like a button.
	class TextField : public Button
	{

		/// @brief Text to be displayed when nothing was written.
		sf::String emptyFieldPlaceholder;

		/// @brief Information whether to hide the placeholder when the field is 'active' or only once text is inserted.
		bool hidePlaceholderWhenSelected;

		/// @brief Information whether the textbox is selcted or not.
		/// If true (selected), input will not be ignored.
		bool selected;

	public:

		/// @brief Set the placeholder mode.
		/// @param option True - hide placeholder when field is selected, false - hide placeholder when input is detected
		virtual void setEmptyPlaceholderMode(const bool option);

		/// @brief Get the placeholder mode.
		/// @return True - placeholder is hiden when field is selected, false - placeholder is hidden when input is detected
		bool getEmptyPlaceholderMode() const;

		/// @brief Set placeholder text.
		/// @param placeholder Placeholder text
		void setEmptyPlaceholder(const sf::String& placeholder);

		/// @brief Get user input from the text field.
		/// @return User-entered characters
		virtual sf::String getInput();

		/// @brief Set the text field to it's default state.
		/// Removes contents, unselects and displays placeholder.
		virtual void reset();

		/// @brief Checks whether the field is selected and ready to receive input.
		/// @return True if text can be entered, false otherwise.
		bool isSelected() const;

		/// @brief Main function handling text field input.
		/// Should be executed for every TextEntered event and mouse event, can be safely executed for every event.
		/// 
		/// @param pointerPos Mouse pointer position
		/// @param event SFML Event
		virtual void onEvent(const sf::Vector2f& pointerPos, const sf::Event& event);

	};

}