#pragma once

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;

	Rect(float x1, float y1, float x2, float y2);
	Rect();

	inline float getWidth() const
	{
		return  x2 - x1;
	}

	inline float getHeight() const
	{
		return y2 - y1;
	}
};