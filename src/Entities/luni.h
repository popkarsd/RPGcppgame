#pragma once
#include "entity.h"
#include "settings.h"

namespace objects

{
class Luni : public Entity
{
	sf::Vector2i horizontalPresses = {0,0}; //x is left, y is right
public:
	Luni();
	void horizontal_movement();
	void implement_velocities();
	void check_floor();
	void horizontal_sm(sf::Keyboard::Key input, bool press);
	void vertical_sm(sf::Keyboard::Key input, bool press);
	void handle_input(sf::Keyboard::Key input);
	void get_state();
	void update(std::vector <sf::Sprite*>& spriteVec);
	void set_texture(const sf::Texture& texture);
};
}