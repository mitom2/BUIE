#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "animation.hpp"

namespace buie
{
	namespace animated
	{

		/// @brief Clickable button with a text label and animation on press and release (reverse of press animation).
		/// Buttons should not be rotated.
		class Button : public buie::Button
		{
			/// @brief Press (and reversed release) animation.
			buie::animated::Animation pressAnimation;

			/// @brief Button texture.
			sf::Texture* buttonAnimatedTexture;

		public:

			/// @brief Default constructor.
			/// Create button with no animation
			Button();

			/// @brief Create button with specified click animation.
			/// @param animation Press animation
			Button(const Animation& animation);

			/// @brief Set new click animation.
			/// @param animation Press animation
			void setAnimation(const buie::animated::Animation& animation);

			/// @brief Get pointer to press animation.
			/// @return Pointer to animation
			Animation* getAnimationPtr();

			/// @brief Checks whether the object is currently pressed down and advances animation if needed.
			/// @param fps Frames per second
			/// @return True if the object is pressed, false otherwise
			virtual bool isPressed(const double fps);

			/// @brief Checks whether the object was pressed and enables animation if needed.
			/// Checks whether mouse button transition from released to pressed happened and if it happened within the object's global bounds.
			/// 
			/// @param pointerPos Mouse pointer position
			/// @param event SFML Event
			/// @return True if the object was pressed, false otherwise
			virtual bool isPressed(const sf::Vector2f& pointerPos, const sf::Event::EventType& event) override;

			/// @brief Checks whether the object was released and enables animation if needed.
			/// Checks whether mouse button transition from pressed to released happened and if it happened within the object's global bounds.
			/// 
			/// @param pointerPos Mouse pointer position
			/// @param SFML Event
			/// @return True if the object was released, false otherwise
			virtual bool isReleased(const sf::Vector2f& pointerPos, const sf::Event::EventType& event) override;

			/// @brief Checks whether the object was clicked, executes function with passed parameters if it was and advances the animation if needed.
			/// Also updates internal variable informing whether the object is clicked.
			/// 
			/// @tparam T Function
			/// @tparam ...args Function parameters
			/// @param fps
			/// @param pointerPos Mouse pointer position
			/// @param event SFML Event
			/// @param functionPtr Function
			/// @param ...params Function Parameters
			template<class T, class... args>
			void check(const double fps, const sf::Vector2f& pointerPos, const sf::Event::EventType& event, T functionPtr, args... params) //This method's definition must be included in the header file in order to compile properly
			{
				if (buie::animated::Button::isPressed(fps) == true)
				{
					if (buie::animated::Button::isReleased(pointerPos, event) == true)
					{
						functionPtr(params...);
					}
				}
				else
					buie::animated::Button::isPressed(pointerPos, event);
			}
		};
	}
}