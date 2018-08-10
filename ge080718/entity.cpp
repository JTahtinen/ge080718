#include "entity.h"
#include "subject.h"
#include "globals.h"
#include "game.h"

unsigned int Entity::NUM_ENTITIES = 0;

Entity::Entity(float x, float y)
	: _id(nextId())
	, _pos(x, y)
{
	subject = new Subject();
	Log::msg("Created Entity, id: " + std::to_string(_id));
}

Entity::Entity(const Vec2& pos)
	: Entity(pos.x, pos.y)
{
}

Entity::Entity()
	: Entity(0, 0)
{	
}

void Entity::update(Game* game)
{
	_pos = nextPos();
	if (_vel.length() != 0.0f)
	{
		subject->notify(this, ENTITY_MOVED);
	}
}

const Vec2& Entity::getPos() const
{
	return _pos;
}

const Vec2& Entity::getVel() const
{
	return _vel;
}

Vec2 Entity::nextPos() const
{
	return _pos + _vel * Game::frameTime;
}

unsigned int Entity::getId() const
{
	return _id;
}

bool Entity::isMoving() const
{
	return _vel.length() > 0.0f;
}

unsigned int Entity::nextId()
{
	return NUM_ENTITIES++;
}