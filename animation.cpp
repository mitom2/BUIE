#include "animation.hpp"

buie::animated::Animation::Animation()
{
	buie::animated::Animation::elapsedTime = 0;
	buie::animated::Animation::frameLength = 0;
	buie::animated::Animation::frame = 0;
	buie::animated::Animation::reversedDirection = false;
}

buie::animated::Animation::Animation(const std::string& path, const std::string& extension)
{
	std::ifstream fileChecker;
	std::size_t i = 0;
	while (true)
	{
		fileChecker.open(path + (path[path.length() - 1] == '/' ? "" : "/") + std::to_string(i) + extension);
		if (fileChecker.good() == false)
			break;
		buie::animated::Animation::frames.push_back(new sf::Texture);
		buie::animated::Animation::frames.back()->loadFromFile("path/" + std::to_string(i) + extension);
	}
	buie::animated::Animation::elapsedTime = 0;
	buie::animated::Animation::frameLength = 0;
	buie::animated::Animation::frame = 0;
	buie::animated::Animation::reversedDirection = false;
}

buie::animated::Animation::Animation(const buie::animated::Animation& srcAnimation)
{
	buie::animated::Animation::elapsedTime = 0;
	buie::animated::Animation::frame = 0;
	buie::animated::Animation::frameLength = srcAnimation.getFrameLength();
	buie::animated::Animation::reversedDirection = !srcAnimation.getOrder();
	for (std::size_t i = 0; i < srcAnimation.getAnimationSize(); i++)
	{
		buie::animated::Animation::frames.push_back(new sf::Texture(srcAnimation.getFrameCopy(i)));
	}
}

void buie::animated::Animation::setOrder(const bool order)
{
	buie::animated::Animation::reversedDirection = !order;
}

bool buie::animated::Animation::getOrder() const
{
	return !(buie::animated::Animation::reversedDirection);
}

bool buie::animated::Animation::isFirstFrame() const
{
	return buie::animated::Animation::frame == 0;
}

bool buie::animated::Animation::isLastFrame() const
{
	return buie::animated::Animation::frame == buie::animated::Animation::frames.size() - 1;
}

sf::Texture buie::animated::Animation::getFrameCopy(std::size_t pos) const
{
	return pos < buie::animated::Animation::frames.size() ? *(buie::animated::Animation::frames[pos]) : sf::Texture();
}

void buie::animated::Animation::setLength(const double length)
{
	if (buie::animated::Animation::frames.size() == 0)
		return;
	buie::animated::Animation::frameLength = length / ((double)(buie::animated::Animation::frames.size()));
}

double buie::animated::Animation::getLength() const
{
	return buie::animated::Animation::frameLength * ((double)(buie::animated::Animation::frames.size()));
}

double buie::animated::Animation::getFrameLength() const
{
	return buie::animated::Animation::frameLength;
}

bool buie::animated::Animation::animate(const double fps, sf::Texture*& updateTexturePtr)
{
	buie::animated::Animation::elapsedTime += 1.0 / fps;
	if (buie::animated::Animation::elapsedTime >= buie::animated::Animation::frameLength)
	{
		updateTexturePtr = buie::animated::Animation::advanceFrame(1);
		buie::animated::Animation::elapsedTime = 0;
		return true;
	}
	return false;
}

sf::Texture* buie::animated::Animation::getFrame()
{
	return buie::animated::Animation::frames[buie::animated::Animation::frame];
}

sf::Texture* buie::animated::Animation::getFrame(std::size_t pos)
{
	return pos <= buie::animated::Animation::frames.size() ? buie::animated::Animation::frames[pos] : nullptr;
}

sf::Texture* buie::animated::Animation::setFrame(std::size_t pos)
{
	return pos <= buie::animated::Animation::frames.size() ? buie::animated::Animation::frames[buie::animated::Animation::frame = pos] : nullptr;
}

std::size_t buie::animated::Animation::currentFrame() const
{
	return buie::animated::Animation::frame;
}

sf::Texture* buie::animated::Animation::advanceFrame(int amount)
{
	while (amount != 0)
	{
		if (amount + buie::animated::Animation::frame >= buie::animated::Animation::frames.size())
		{
			amount -= buie::animated::Animation::frames.size() - buie::animated::Animation::frame;
			buie::animated::Animation::frame = 0;
		}
		else if (amount + buie::animated::Animation::frame < 0)
		{
			amount += buie::animated::Animation::frame;
			buie::animated::Animation::frame = buie::animated::Animation::frames.size();
		}
		else
		{
			buie::animated::Animation::frame += amount;
			break;
		}
	}
	return buie::animated::Animation::frames[buie::animated::Animation::frame];
}

std::size_t buie::animated::Animation::getAnimationSize() const
{
	return buie::animated::Animation::frames.size();
}

sf::Texture* buie::animated::Animation::operator++()
{
	return buie::animated::Animation::advanceFrame(1);
}

sf::Texture* buie::animated::Animation::operator++(int)
{
	sf::Texture* b = buie::animated::Animation::getFrame();
	buie::animated::Animation::advanceFrame(1);
	return b;
}

sf::Texture* buie::animated::Animation::operator--()
{
	return buie::animated::Animation::advanceFrame(-1);
}

sf::Texture* buie::animated::Animation::operator--(int)
{
	sf::Texture* b = buie::animated::Animation::getFrame();
	buie::animated::Animation::advanceFrame(-1);
	return b;
}

buie::animated::Animation::~Animation()
{
	for (std::size_t i = 0; i < buie::animated::Animation::frames.size(); i++)
	{
		delete buie::animated::Animation::frames[i];
	}
}