#pragma once
#include "entity.h"
#include "surface.h"
class Light : public Entity
{
	static float*	INTENSITY_TABLE;
	static float	INTENSITY_TABLE_RADIUS;
	float			_radius;
	float			_intensity;
	bool			_active;
public:
	Light(float x, float y, float radius, float intensity, bool active);
	Light(const Vec2& pos, float radius, float intensity, bool active);
	Light(float x, float y, float radius, float intensity);
	Light(const Vec2& pos, float radius, float intensity);
	Light(float x, float y);
	Light(const Vec2& pos);
	Light();
	bool isActive() const;
	void flip();
	void render(float* buffer, int bufferWidth, int bufferHeight, const Vec2& bufferPos) const;
	float getIntensityAtDistance(float distance) const;
	bool isInRadiusOf(const Vec2& pos) const;

	static void loadAssets();
	static void deleteAssets();

	inline float getModifier(float distance) const
	{
		return INTENSITY_TABLE[(int)(INTENSITY_TABLE_RADIUS / (_radius / distance))] * _intensity;
	}
};