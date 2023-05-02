#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

namespace buie
{

	/// @brief Object capable of detecting basic user interaction.
	/// Clickable objects should not be rotated - detection algorithms will not work properly.
	class Clickable : public sf::RectangleShape
	{
		/// @brief Holds the information whether this object is currently pressed.
		bool objectPressed;

	public:

		/// @brief Checks whether the object is currently pressed down.
		/// @return True if the object is pressed, false otherwise
		virtual bool isPressed() const;

		/// @brief Checks whether the object was clicked and executes function with passed parameters if it was.
		/// Also updates internal variable informing whether the object is clicked.
		/// 
		/// @tparam T Function
		/// @tparam ...args Function parameters
		/// @param pointerPos Mouse pointer position
		/// @param event SFML Event
		/// @param functionPtr Function
		/// @param ...params Function Parameters
		template<class T, class... args>
		void check(const sf::Vector2f& pointerPos, const sf::Event::EventType& event, T functionPtr, args... params) //This method's definition must be included in the header file in order to compile properly
		{
			if (buie::Clickable::objectPressed == true)
			{
				if (buie::Clickable::isReleased(pointerPos, event) == true)
				{
					functionPtr(params...);
				}
			}
			else
				buie::Clickable::isPressed(pointerPos, event);
		}

		/// @brief Checks whether the object was pressed.
		/// Checks whether mouse button transition from released to pressed happened and if it happened within the object's global bounds.
		/// 
		/// @param pointerPos Mouse pointer position
		/// @param event SFML Event
		/// @return True if the object was pressed, false otherwise
		virtual bool isPressed(const sf::Vector2f& pointerPos, const sf::Event::EventType& event);

		/// @brief Checks whether the object was released.
		/// Checks whether mouse button transition from pressed to released happened and if it happened within the object's global bounds.
		/// 
		/// @param pointerPos Mouse pointer position
		/// @param SFML Event
		/// @return True if the object was released, false otherwise
		virtual bool isReleased(const sf::Vector2f& pointerPos, const sf::Event::EventType& event);

		/// @brief Checks whether pointer is hovering over the object's global bounds.
		/// @param pointerPos Mouse pointer position
		/// @return True if mouse pointer is hovering, false otherwise
		virtual bool isHovered(const sf::Vector2f& pointerPos) const;

	};

}