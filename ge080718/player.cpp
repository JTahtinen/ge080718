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

void Player::update(Game* game)
{
	static float speed = 5.0f;
	_vel *= 0;
	Map* map = game->getGameData().map;
	Usable* potentialTarget = map->getEntityFromAbsPos(_pos.x + 48, _pos.y);
	static bool lostTarget = false;
	
	if (potentialTarget != _target)
	{
		_target = potentialTarget;
		if (_target)
		{
			_target->target();
		}
		else
		{
			lostTarget = true;
		}
	}
	
	if (!potentialTarget && lostTarget)
	{
		Log::msg("Lost target");
		lostTarget = false;
	}
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
			_target->use();
		}
	}
	Actor::update(game);
}