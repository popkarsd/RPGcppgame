#include "luni.h"
#include "entity.h"
#include "settings.h"

using namespace objects;

Luni::Luni()
{
	sprite.setPosition(400, settings::floor_y);
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, settings::g);
	facing_state = STATE_FACING_LEFT;
	horizontal_state = STATE_STILL;
	vertical_state = STATE_STANDING;
}

void Luni::horizontal_sm(sf::Keyboard::Key input, bool press)
{
	if (input == sf::Keyboard::D || input == sf::Keyboard::Right || input == sf::Keyboard::A || input == sf::Keyboard::Left)
	{
		if (press && horizontalPresses.x == 0 && (input == sf::Keyboard::A || input == sf::Keyboard::Left))
		{
			horizontalPresses.x++;
		}
		if (press && horizontalPresses.y == 0 && (input == sf::Keyboard::D || input == sf::Keyboard::Right))
		{
			horizontalPresses.y++;
		}
		if (!press && horizontalPresses.x == 1 && (input == sf::Keyboard::A || input == sf::Keyboard::Left))
		{
			horizontalPresses.x--;
		}
		if (!press && horizontalPresses.y == 1 && (input == sf::Keyboard::D || input == sf::Keyboard::Right))
		{
			horizontalPresses.y--;
		}
	}
	if (horizontalPresses == sf::Vector2i(1, 1) || horizontalPresses == sf::Vector2i(0, 0))
	{
		horizontal_state = STATE_STILL;
	}
	else
	{
		if (horizontalPresses.x)
		{
			horizontal_state = STATE_MOVING_LEFT;
		}
		if (horizontalPresses.y)
		{
			horizontal_state = STATE_MOVING_RIGHT;
		}
	}
}

void Luni::vertical_sm(sf::Keyboard::Key input, bool press)
{
	switch (vertical_state)
	{
		case STATE_STANDING:
			if ((input == sf::Keyboard::Space || input == sf::Keyboard::Up) && press == true)
			{
				vertical_state = STATE_JUMPING;
				setvel(sf::Vector2f(0, -settings::jump_vel));
			}
			break;
		case STATE_JUMPING:
			break;
		case STATE_DUCKING:
			break;
	}
}

void Luni::set_texture(const sf::Texture& texture)
{

	sprite.setTexture(texture);
}

void Luni::get_state()
{
}
void Luni::update(std::vector<sf::Sprite*>& spriteVec)
{
	//update horizontal state
	horizontal_mov();
	/*
	if (horizontal_state == STATE_MOVING_RIGHT)
	{
		std::cout << "RIGHT" << std::endl;
	}
	if (horizontal_state == STATE_MOVING_LEFT)
	{
		std::cout << "LEFT" << std::endl;
	}
	if (horizontal_state == STATE_STILL)
	{
		std::cout << "STILL" << std::endl;
	}
	*/

	//update vertical state
	//vertical_mov();

	//update physics
	velocity += acceleration;
	sprite.move(velocity);

	if (sprite.getPosition().y + sprite.getGlobalBounds().height >= floor_y && velocity.y >= 0)
	{
		vertical_state = STATE_STANDING;
		sprite.setPosition(sprite.getPosition().x, floor_y - sprite.getGlobalBounds().height);
		velocity.y = 0;
	}

	std::vector<sf::Sprite*> collidedRects;
	collidedRects = check_collision(spriteVec);
	collision_move(collidedRects);

	//update firing state

	//physics that always applies

	//update facing direction
	if (velocity.x > 0)
	{
		if (facing_state == STATE_FACING_LEFT)
		{
			sprite.setScale(-1.f, 1.f);
			sprite.move(sprite.getLocalBounds().width, 0);
		}
		facing_state = STATE_FACING_RIGHT;
	}
	else if (velocity.x < 0)
	{
		if (facing_state == STATE_FACING_RIGHT)
		{
			sprite.setScale(1.f, 1.f);
			sprite.move(-sprite.getLocalBounds().width, 0);
		}
		facing_state = STATE_FACING_LEFT;
	}
}
