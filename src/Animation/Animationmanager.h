#pragma once
#include <filesystem>

namespace animation

{

class Animationmanager
{
protected:
	sf::IntRect curRect = { 0, 0, 0, 0 };
	int framesPerMove = 3;
	int curFrames = 0;
	bool playing;
	unsigned int horizontalStepSize = 0;
	unsigned int verticalStepSize = 0;
	sf::Sprite* spritePtr;
	sf::Texture* texture;

public:
	Animationmanager();
	Animationmanager(sf::Sprite*, sf::Texture*, int, int);
	void nextFrame();
	void toggleAnimation(bool);
};

}