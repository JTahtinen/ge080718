#include "player.h"
#include "testdata.h"
#include "input.h"
#include "map.h"
#include "game.h"

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

void Player::update(Game* game)
{
	handleInput();
	Actor::update(game);
	_vel *= 0;
}

void Player::handleInput()
{
	Input& in = Input::instance();
	if (in.poll(SDLK_UP))
	{
		pushTask(MOVE_UP);
	}
	if (in.poll(SDLK_DOWN))
	{
		pushTask(MOVE_DOWN);
	}
	if (in.poll(SDLK_LEFT))
	{
		pushTask(MOVE_LEFT);
	}
	if (in.poll(SDLK_RIGHT))
	{
		pushTask(MOVE_RIGHT);
	}
	if (in.poll(SDLK_f, KEY_TYPED))
	{
		pushTask(ACTIVATE_TARGET);
	}
	if (in.poll(SDLK_TAB, KEY_TYPED))
	{
		pushTask(SWITCH_TARGET);
	}
}