#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>

namespace buie
{

	/// @brief Provides very basic support for simple animations.
	/// Keep in mind that, unlike some other solutions, animations here are created using frames located in separate files and not with spritesheets.
	/// Multiple objects can use the same animation, but the default animate method can not be easily used for all of them. It is recommended (but not required) to create separate Animation instance for every animatable object.
	class Animation
	{
		/// @brief Individual frames of the animation.
		std::vector<sf::Texture*> frames;

		/// @brief Position of currently displayed frame.
		std::size_t frame;

		/// @brief Approximate time that the current frame have been displayed for, expressed in seconds.
		double elapsedTime;

		/// @brief Length of a single frame, expressed in seconds.
		double frameLength;

	public:

		/// @brief Creates animation from source.
		/// The source should be a directory containing all animation frames located in separate files, named in ascending order with arabic numerals.
		/// Example: '0.png', '1.png', '2.png', '3.png'
		/// 
		/// @param path Path to source directory
		/// @param extension Image format used (with dot prefix)
		Animation(const std::string& path, const std::string& extension);

		/// @brief Set target length of the animation.
		/// Entered value is not guaranteed to be achieved exactly.
		/// 
		/// @param length Target animation langth, expressed in seconds
		void setLength(const double length);

		/// @brief Get target length of the animation.
		/// @return Target time, expressed in seconds
		double getLength() const;

		/// @brief Get target length of the single animation frame.
		/// @return Target time, expressed in seconds
		double getFrameLength() const;

		/// @brief Default animation handling.
		/// Should be called once before every display. Calculates approximate elapsed time of frame and switches to the next one if time threshold is reached.
		/// 
		/// @param fps Frames per second
		/// @param updateTexturePtr Reference to the texture pointer of animated object
		/// @return True if frame was changed, false otherwise
		bool animate(const double fps, sf::Texture*& updateTexturePtr);

		/// @brief Get currently displayed animation frame.
		/// @return Pointer to frame
		sf::Texture* getFrame();

		/// @brief Get animation frame from any position.
		/// If the requested position is larger than animation size, nullptr is returned.
		/// @param pos Frame number
		/// @return Pointer to frame or nullptr if it does not exist
		sf::Texture* getFrame(std::size_t pos);

		/// @brief Set current animation frame to any position.
		/// If the requested position is larger than animation size, nullptr is returned and no change is made.
		/// @param pos Frame number
		/// @return Pointer to frame or nullptr if it does not exist
		sf::Texture* setFrame(std::size_t pos);

		/// @brief Get current frame's position
		/// @return Position of current frame
		std::size_t currentFrame() const;

		/// @brief Moves tha animation by the slected amount of frames.
		/// Positive values will move the animation forward, and negative backwards.
		/// If internal position counter readches negative values or values greater than animation size, it will be set to the other end of the animation (the animation will be looped).
		/// 
		/// @param amount Amount of frames to advance
		/// @return Pointer to frame
		sf::Texture* advanceFrame(int amount);

		/// @brief Get number of frames in the animation.
		/// @return Number of frames
		std::size_t getAnimationSize() const;

		/// @brief Switches to the next frame and returns it.
		/// @return Pointer to frame
		sf::Texture* operator++();

		/// @brief Returns current frame and then switches to the next one.
		/// @return Pointer to frame
		sf::Texture* operator++(int);

		/// @brief Switches to the previous frame and returns it.
		/// @return Pointer to frame
		sf::Texture* operator--();

		/// @brief Returns current frame and then switches to the previous one.
		/// @return Pointer to frame
		sf::Texture* operator--(int);

		/// @brief Default destructor.
		/// Deletes all saved frames
		~Animation();

	};

}