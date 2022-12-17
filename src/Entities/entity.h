#pragma once
#include "settings.h"

//enums
enum Horizontal_state
{
	STATE_STILL,
	STATE_MOVING_RIGHT,
	STATE_MOVING_LEFT
};

enum Vertical_state
{
	STATE_STANDING,
	STATE_JUMPING,
	STATE_DUCKING
};

enum Facing_state
{
	STATE_FACING_LEFT,
	STATE_FACING_RIGHT
};

namespace objects

{

class Entity
{
protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Sprite sprite;

	enum Horizontal_state horizontal_state;
	enum Vertical_state vertical_state;
	enum Facing_state facing_state;

	bool left_collided = false;
	bool right_collided = false;
	bool on_floor = true;
	float floor_y = settings::floor_y;

public:
	Entity();
	sf::Vector2f getvel();
	void setvel(sf::Vector2f vel);
	sf::Vector2f getacc();
	void setacc(sf::Vector2f acc);
	sf::Sprite* get_sprite();
	void horizontal_mov();
	void vertical_mov();
	sf::FloatRect getRect();
	void update();
	std::vector<sf::Sprite*> check_collision(std::vector<sf::Sprite*>& spriteVec);
	void collision_move(std::vector<sf::Sprite*>& spriteVec);
};
}