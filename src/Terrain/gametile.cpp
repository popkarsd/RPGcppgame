#include "gametile.h"
#include "settings.h"

using namespace gametile;

//todo: free memory usage by loading texture outside of class

Gametile::Gametile(std::string textureName, sf::Vector2f pos, bool passable, bool exit)
{
	if (!setUpSprite(textureName))
	{
		std::cerr << "can't load tile texture" << std::endl;
		return;
	}
	is_exit = exit;
	is_passable = passable;
	position = pos * 32.0f;
	sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	sprite.setPosition(position);
}

bool Gametile::setUpSprite(std::string texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	return true;
}
sf::FloatRect Gametile::getRect()
{
	return (
		sf::FloatRect(
			position.x,
			position.y,
			sprite.getTextureRect().width,
			sprite.getTextureRect().height));
}
sf::Sprite* Gametile::getSprite()
{
	return &sprite;
}
bool Gametile::passable()
{
	return is_passable;
}