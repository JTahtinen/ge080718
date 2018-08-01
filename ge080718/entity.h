#pragma once
#include "surface.h"
#include "vec2.h"

class Subject;

class Entity
{
protected:
	static unsigned int		NUM_ENTITIES;
	unsigned int			_id;
	Vec2					_pos;
	Vec2					_vel;
public:
	Subject*				subject;
public:
	Entity(float x, float y);
	Entity(const Vec2& pos);
	Entity();
	virtual void update() {};
	const Vec2& getPos() const;
	const Vec2& getVel() const;
	unsigned int getId() const;
};