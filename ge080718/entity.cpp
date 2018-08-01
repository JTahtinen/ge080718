#include "entity.h"
#include "subject.h"
#include "globals.h"

unsigned int Entity::NUM_ENTITIES = 0;

Entity::Entity(float x, float y)
	: _id(NUM_ENTITIES++)
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

const Vec2& Entity::getPos() const
{
	return _pos;
}

const Vec2& Entity::getVel() const
{
	return _vel;
}

unsigned int Entity::getId() const
{
	return _id;
}