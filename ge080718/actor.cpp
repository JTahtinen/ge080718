#include "actor.h"
#include "testdata.h"

Actor::Actor(float x, float y, const Material* sprite)
	: _ai(nullptr)
	, WorldObject(x, y, sprite)
	
{
}

Actor::Actor(const Vec2& pos)
	: Actor(pos.x, pos.y, TestData::instance().dudeMat)
{
}

Actor::Actor()
	: Actor(0, 0, TestData::instance().dudeMat)
{
}

void Actor::update(const Game* game)
{
	if (_ai)
	{
		_ai->update(this);
	}
	WorldObject::update(game);
}

void Actor::move(const Vec2& dir, float speed)
{
	_vel = dir.getNormal() * speed;
}

void Actor::setAI(AI* ai)
{
	_ai = ai;
}

void Actor::addHostile(const Actor* actor)
{
	_state.addHostile(actor);
	_state.setMood(ACTIVE);
}