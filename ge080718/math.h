#pragma once
#include <math.h>
#include "vec2.h"

#define PI 3.14159f
namespace math
{
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

	inline bool inBounds(float value, float floor, float ceil)
	{
		return (value >= floor && value < ceil);
	}

	inline bool inBounds(float x, float y, float xFloor, float yFloor, float xCeil, float yCeil)
	{
		return (inBounds(x, xFloor, xCeil) && inBounds(y, yFloor, yCeil));
	}
}