#include "player.h"
#include "testdata.h"
#include "input.h"
#include "map.h"
#include "game.h"

Player::Player(float x, float y, const Material* sprite)
	: Actor(x, y, sprite)
	, _target(nullptr)
{
}

Player::Player(const Vec2& pos, const Material* sprite)
	: Player(pos.x, pos.y, sprite)
{
}

Player::Player()
	: Player(0.0f, 0.0f, TestData::instance().dudeMat)
{
}
#include <iostream>
void Player::update(Game* game)
{
	static float speed = 5.0f;
	_vel *= 0;
	Map* map = game->getGameData().map;
	std::vector<FixedEntity*> entities = map->getEntitiesFromArea(_pos, 4);
	static unsigned int entityIndex = 0;
	static bool cycleEntityIndex = false;
	

	static Usable* potentialTarget = nullptr;

	
	if (entities.size() > 0)
	{
		unsigned int i = 0;
		float distance = math::distance(_pos, entities[i]->getPos());
		std::cout << "Distance[0]: " << distance << std::endl;
		for (unsigned int j = 1; j < entities.size(); ++j)
		{
			float newDistance = math::distance(_pos, entities[j]->getPos());
			std::cout << "distance[" << j << "]: " << newDistance << std::endl;
			if (newDistance < distance)
			{
				distance = newDistance;
				i = j;
			}
		}
		entityIndex = i;
		if (cycleEntityIndex)
		{
			++entityIndex;
			if (entityIndex > entities.size() - 1)
			{
				entityIndex = 0;
			}
			cycleEntityIndex = false;
		}
		potentialTarget = entities[entityIndex];
	}
	

	if (potentialTarget != _target)
	{
		if (_target)
		{
			_target->target(false);
		}
		_target = potentialTarget;
		if (_target)
		{
			_target->target(true);
		}
	}

	if (entities.empty()) potentialTarget = nullptr;
	
	Input& in = Input::instance();
	if (in.poll(SDLK_UP))
	{
		_vel.add(0.0f, -speed);
	}
	if (in.poll(SDLK_DOWN))
	{
		_vel.add(0.0f, speed);
	}
	if (in.poll(SDLK_LEFT))
	{
		_vel.add(-speed, 0.0f);
	}
	if (in.poll(SDLK_RIGHT))
	{
		_vel.add(speed, 0.0f);
	}
	if (in.poll(SDLK_f, KEY_TYPED))
	{
		if (_target)
		{
			_target->use(this);
		}
	}
	if (in.poll(SDLK_TAB, KEY_TYPED))
	{
		cycleEntityIndex = true;
	}
	Actor::update(game);
}