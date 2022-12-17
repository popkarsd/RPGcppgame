#include "entity.h"
#include "settings.h"
#include <algorithm>
#include <iostream>

using namespace objects;

Entity::Entity()
{
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, settings::g);
	facing_state = STATE_FACING_LEFT;
	horizontal_state = STATE_STILL;
	vertical_state = STATE_STANDING;
}
sf::Vector2f Entity::getvel()
{
	return velocity;
}

void Entity::setvel(sf::Vector2f vel)
{
	velocity = vel;
}

sf::Vector2f Entity::getacc()
{
	return acceleration;
}
void Entity::setacc(sf::Vector2f acc)
{
	acceleration = acc;
}
sf::Sprite* Entity::get_sprite()
{
	return &sprite;
}

void Entity::horizontal_mov()
{
	switch (horizontal_state)
	{
		case STATE_STILL:
			right_collided = false;
			left_collided = false;
			velocity.x = 0;
			break;
		case STATE_MOVING_RIGHT:
			if (right_collided)
			{
				break;
			}
			velocity.x = 7;
			break;
		case STATE_MOVING_LEFT:
			if (left_collided)
			{
				break;
			}
			velocity.x = -7;
	}
}

void Entity::update()
{
	//update horizontal state
	horizontal_mov();

	//update vertical state
	//vertical_mov();

	//update physics
	velocity += acceleration;
	sprite.move(velocity);

	if (sprite.getPosition().y >= floor_y)
	{
		vertical_state = STATE_STANDING;
		sprite.setPosition(sprite.getPosition().x, floor_y);
		velocity.y = 0;
	}

	//update facing direction
	if (velocity.x > 0)
	{
		if (facing_state == STATE_FACING_LEFT)
		{
			sprite.setScale(-1.f, 1.f);
		}
		facing_state = STATE_FACING_RIGHT;
	}
	else if (velocity.y < 0)
	{
		if (facing_state == STATE_FACING_RIGHT)
		{
			sprite.setScale(-1.f, 1.f);
		}
		facing_state = STATE_FACING_RIGHT;
	}
}

std::vector<sf::Sprite*> Entity::check_collision(std::vector<sf::Sprite*>& spriteVec)
{
	sf::FloatRect ownrect = sprite.getGlobalBounds();
	std::vector<sf::Sprite*> collided_objs;
	for (auto s : spriteVec)
	{
		if (ownrect.intersects(s->getGlobalBounds()))
		{
			collided_objs.push_back(s);
		}
	}

	return collided_objs;
}

void Entity::collision_move(std::vector<sf::Sprite*>& collidedSpriteVec)
{
	sf::Vector2f seperationVec = { 0, 0 };
	sf::FloatRect spriteRect = sprite.getGlobalBounds();

	//argument is of collided rect
	if (collidedSpriteVec.empty())
	{
		floor_y = settings::floor_y;
		return;
	}

	for (auto collidedSprite : collidedSpriteVec)
	{
		sf::FloatRect collidedRect = collidedSprite->getGlobalBounds();
		//if goes on top of collided obj
		//does this if it doesn't come in contact with bottom 60% of the object
		if (spriteRect.top + spriteRect.height < collidedRect.top + collidedRect.height * 0.4)
		{
			seperationVec.y = collidedRect.top - (spriteRect.top + spriteRect.height);
			floor_y = std::fmin(floor_y, collidedRect.top);
			continue;
		}
		//bot
		if (spriteRect.top > collidedRect.top + collidedRect.height * 0.6)
		{
			seperationVec.y = (collidedRect.top + collidedRect.height) - spriteRect.top;
			velocity.y = 0;
		}
		//left
		if (spriteRect.left > collidedRect.left + collidedRect.width * 0.6)
		{
			seperationVec.x = (collidedRect.left + collidedRect.width) - spriteRect.left;
			left_collided = true;
			velocity.x = 0;
		}
		//right
		if (spriteRect.left + spriteRect.width < collidedRect.left + collidedRect.width * 0.4)
		{
			seperationVec.x = collidedRect.left - (spriteRect.left + spriteRect.width);
			right_collided = true;
			velocity.x = 0;
		}
	}

	sprite.move(seperationVec);
	std::cout << seperationVec.x << " " << seperationVec.y << std::endl;
}