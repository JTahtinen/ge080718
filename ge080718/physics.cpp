#include "physics.h"
#include "globals.h"
#include <iostream>

bool Physics::overlaps(const Rect& box1, const Rect& box2) const
{
	return 
		(((box1.x1 >= box2.x1 && box1.x1 <= box2.x2) || (box1.x2 >= box2.x1 && box1.x2 <= box2.x2)) // X-overlap
		&&
		((box1.y1 >= box2.y1 && box1.y1 <= box2.y2) || (box1.y2 >= box2.y1 && box1.y2 <= box2.y2))); // Y-overlap
}

Collision Physics::collision(const Rect& box1, const Vec2& vel, const Rect& box2) const
{
	Rect xBox = {
		box1.x1 + vel.x,
		box1.y1,
		box1.x2 + vel.x,
		box1.y2 
	};
	Rect yBox = {
		box1.x1,
		box1.y1 + vel.y,
		box1.x2, 
		box1.y2 + vel.y,
	};

	bool xCollision = overlaps(xBox, box2);
	bool yCollision = overlaps(yBox, box2);
	return { xCollision, yCollision };
}

Vec2 Physics::calcFriction(float friction, const Vec2& vel) const
{
	if (friction == 0)
	{
		return vel;
	}
	return Vec2(vel.x / friction, vel.y / friction);
}