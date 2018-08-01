#pragma once
#include "rect.h"
#include "vec2.h"
#include "material.h"

struct Collision
{
	bool xCollision;
	bool yCollision;
};

class Physics
{
public:
	bool overlaps(const Rect& box1, const Rect& box2) const;
	Collision collision(const Rect& box1, const Vec2& vel, const Rect& box2) const;
	Vec2 calcFriction(float friction, const Vec2& vel) const;


	inline static const Physics& instance()
	{
		static Physics physics;
		return physics;
	}
};