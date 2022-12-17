#pragma once
#include "settings.h"

namespace gametile

{

class Gametile
{
protected:
	bool is_passable;
	bool is_exit;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Gametile(std::string, sf::Vector2f, bool, bool);
	bool setUpSprite(std::string);
	sf::Sprite* getSprite();
	sf::FloatRect getRect();
	bool passable();
};

}