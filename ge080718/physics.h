#pragma once
#include "rect.h"
#include "vec2.h"
#include "material.h"

typedef Rect Collider;

struct Collision
{
	bool xCollision;
	bool yCollision;
};

class Physics
{
public:
	bool overlaps(const Collider& box1, const Collider& box2) const;
	Collision collision(const Collider& box1, const Vec2& vel, const Collider& box2) const;
	Vec2 calcFriction(float friction, const Vec2& vel) const;


	inline static const Physics& instance()
	{
		static Physics physics;
		return physics;
	}
};