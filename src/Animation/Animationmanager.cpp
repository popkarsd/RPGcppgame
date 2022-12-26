#include "Animationmanager.h"
#include <algorithm>
#include <filesystem>
#include <iostream>

using namespace animation;

Animationmanager::Animationmanager()
{
}
Animationmanager::Animationmanager(sf::Sprite* sprite, sf::Texture* sheetPtr, int hStep, int vStep)
{
	spritePtr = sprite;
	horizontalStepSize = hStep;
	verticalStepSize = vStep;
	curRect = { 0, 0, hStep, vStep };
	playing = false;
	texture = sheetPtr;
	spritePtr->setTexture(*texture);
	spritePtr->setTextureRect(curRect);
}

void Animationmanager::toggleAnimation(bool state)
{
	playing = state;
}

void Animationmanager::nextFrame()
{
	if (!playing)
	{
		return;
	}
	if (curFrames != framesPerMove)
	{
		curFrames++;
		return;
	}
	curFrames = 0;
	if (unsigned(curRect.left + curRect.width) == texture->getSize().x && unsigned(curRect.top + curRect.height) == texture->getSize().y)
	{
		curRect.left = 0;
		curRect.top = 0;
	}
	else if (unsigned(curRect.left + curRect.width) == texture->getSize().x)
	{
		curRect.left = 0;
		curRect.top += verticalStepSize;
	}
	else
	{
		curRect.left += horizontalStepSize;
	}
	spritePtr->setTextureRect(curRect);
}
