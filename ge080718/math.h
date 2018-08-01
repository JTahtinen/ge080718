#pragma once
#include <math.h>
#include "vec2.h"

#define PI 3.14159f

inline float hypotenuse(float a, float b)
{
	return sqrtf((a * a) + (b * b));
}

inline float distance(float x1, float y1, float x2, float y2)
{
	return hypotenuse(x2 - x1, y2 - y1);
}

inline float distance(const Vec2& pos1, const Vec2& pos2)
{
	return distance(pos1.x, pos1.y, pos2.x, pos2.y);
}