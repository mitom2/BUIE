#include "animation.hpp"

buie::Animation::Animation(const std::string& path, const std::string& extension)
{
	std::ifstream fileChecker;
	std::size_t i = 0;
	while (true)
	{
		fileChecker.open(path + (path[path.length() - 1] == '/' ? "" : "/") + std::to_string(i) + extension);
		if (fileChecker.good() == false)
			break;
		buie::Animation::frames.push_back(new sf::Texture);
		buie::Animation::frames.back()->loadFromFile("path/" + std::to_string(i) + extension);
	}
	buie::Animation::elapsedTime = 0;
	buie::Animation::frameLength = 0;
	buie::Animation::frame = 0;
}

void buie::Animation::setLength(const double length)
{
	if (buie::Animation::frames.size() == 0)
		return;
	buie::Animation::frameLength = length / ((double)(buie::Animation::frames.size()));
}

double buie::Animation::getLength() const
{
	return buie::Animation::frameLength * ((double)(buie::Animation::frames.size()));
}

double buie::Animation::getFrameLength() const
{
	return buie::Animation::frameLength;
}

bool buie::Animation::animate(const double fps, sf::Texture*& updateTexturePtr)
{
	buie::Animation::elapsedTime += 1.0 / fps;
	if (buie::Animation::elapsedTime >= buie::Animation::frameLength)
	{
		updateTexturePtr = buie::Animation::advanceFrame(1);
		buie::Animation::elapsedTime = 0;
		return true;
	}
	return false;
}

sf::Texture* buie::Animation::getFrame()
{
	return buie::Animation::frames[buie::Animation::frame];
}

sf::Texture* buie::Animation::getFrame(std::size_t pos)
{
	return pos <= buie::Animation::frames.size() ? buie::Animation::frames[pos] : nullptr;
}

sf::Texture* buie::Animation::setFrame(std::size_t pos)
{
	return pos <= buie::Animation::frames.size() ? buie::Animation::frames[buie::Animation::frame = pos] : nullptr;
}

std::size_t buie::Animation::currentFrame() const
{
	return buie::Animation::frame;
}

sf::Texture* buie::Animation::advanceFrame(int amount)
{
	while (amount != 0)
	{
		if (amount + buie::Animation::frame >= buie::Animation::frames.size())
		{
			amount -= buie::Animation::frames.size() - buie::Animation::frame;
			buie::Animation::frame = 0;
		}
		else if (amount + buie::Animation::frame < 0)
		{
			amount += buie::Animation::frame;
			buie::Animation::frame = buie::Animation::frames.size();
		}
		else
		{
			buie::Animation::frame += amount;
			break;
		}
	}
	return buie::Animation::frames[buie::Animation::frame];
}

std::size_t buie::Animation::getAnimationSize() const
{
	return buie::Animation::frames.size();
}

sf::Texture* buie::Animation::operator++()
{
	return buie::Animation::advanceFrame(1);
}

sf::Texture* buie::Animation::operator++(int)
{
	sf::Texture* b = buie::Animation::getFrame();
	buie::Animation::advanceFrame(1);
	return b;
}

sf::Texture* buie::Animation::operator--()
{
	return buie::Animation::advanceFrame(-1);
}

sf::Texture* buie::Animation::operator--(int)
{
	sf::Texture* b = buie::Animation::getFrame();
	buie::Animation::advanceFrame(-1);
	return b;
}

buie::Animation::~Animation()
{
	for (std::size_t i = 0; i < buie::Animation::frames.size(); i++)
	{
		delete buie::Animation::frames[i];
	}
}