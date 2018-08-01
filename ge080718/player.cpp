#include "player.h"
#include "testdata.h"
#include "input.h"

Player::Player(float x, float y, const Material* sprite)
	: Actor(x, y, sprite)
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

void Player::update(const Game* game)
{
	static float speed = 5.0f;
	_vel *= 0;
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

	Actor::update(game);
}