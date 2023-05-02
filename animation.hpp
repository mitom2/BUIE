#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>

namespace buie
{
	namespace animated
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

			/// @brief True if animation is to be displayed backwards, false otherwise.
			bool reversedDirection;

		public:

			/// @brief Default constructor.
			/// Creates animation with no frames.
			Animation();

			/// @brief Creates animation from source.
			/// The source should be a directory containing all animation frames located in separate files, named in ascending order with arabic numerals.
			/// Example: '0.png', '1.png', '2.png', '3.png'
			/// 
			/// It is highly recommended to use '/' as directory separator, other signs may cause undefined behaviour.
			/// 
			/// @param path Path to source directory
			/// @param extension Image format used (with dot prefix)
			Animation(const std::string& path, const std::string& extension);

			/// @brief Copy constructor.
			/// New frame pointers and objects are created.
			/// The new animation starts from frame 0, frame elapsed time is also not copied.
			/// 
			/// @param srcAnimation Source animation
			Animation(const buie::animated::Animation& srcAnimation);

			/// @brief Set animation direction.
			/// True for normal, false for backward.
			/// 
			/// @param order Animation order
			void setOrder(const bool order);

			/// @brief Check the animation direction.
			/// @return True if normal, false if backward
			bool getOrder() const;

			/// @brief Checks whether current frame is the first one in animation.
			/// @return True if first, false otherwise
			bool isFirstFrame() const;

			/// @brief Checks whether current frame is the last one in animation.
			/// @return True if last, false otherwise
			bool isLastFrame() const;

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

			/// @brief Get copy of frame.
			/// If the requested position is larger than animation size, empty texture is returned.
			/// 
			/// @param pos Frame position
			/// @return Copied frame
			sf::Texture getFrameCopy(std::size_t pos) const;

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
}