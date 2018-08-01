#include "light.h"
#include "math.h"

float* Light::INTENSITY_TABLE = nullptr;
float Light::INTENSITY_TABLE_RADIUS = 500;

Light::Light(float x, float y, float radius, float intensity, bool active)
	: Entity(x, y)
	, _radius(radius)
	, _intensity(intensity)
	, _active(active)
{
}

Light::Light(const Vec2& pos, float radius, float intensity, bool active)
	: Light(pos.x, pos.y, radius, intensity, active)
{
}

Light::Light(float x, float y, float radius, float intensity)
	: Light(x, y, radius, intensity, true)
{
}

Light::Light(const Vec2& pos, float radius, float intensity)
	: Light(pos, radius, intensity, true)
{
}

Light::Light(float x, float y)
	: Light(x, y, 70.0f, 10.0f)
{
}

Light::Light(const Vec2& pos)
	: Light(pos.x, pos.y)
{
}

Light::Light()
	: Light(0, 0)
{
}

bool Light::isActive() const
{
	return _active;
}

void Light::flip()
{
	_active = !_active;
}

void Light::render(float* buffer, int bufferWidth, int bufferHeight, const Vec2& bufferPos) const
{
	float rSquared = _radius * _radius;
	Vec2 pos;
	for (int y = 0; y < bufferHeight; ++y)
	{
		for (int x = 0; x < bufferWidth; ++x)
		{
			pos.set(bufferPos.x + x, bufferPos.y + y);
			float distanceFromLight = distance(_pos, pos);
			if (distanceFromLight > _radius) continue;
			//float modifier = (_intensity / (PI * (rSquared)) * (_radius - distanceFromLight) * _radius);
			buffer[x + y * bufferWidth] += getModifier(distanceFromLight);
		}
	}
}


float Light::getIntensityAtDistance(float distance) const
{
	return _intensity / distance;
}

bool Light::isInRadiusOf(const Vec2& pos) const
{
	return (distance(_pos, pos) < _radius);
}

void Light::loadAssets()
{
	INTENSITY_TABLE = new float[(int)INTENSITY_TABLE_RADIUS];
	float rSquared = INTENSITY_TABLE_RADIUS * INTENSITY_TABLE_RADIUS;
	for (int i = 0; i < INTENSITY_TABLE_RADIUS; ++i)
	{
		INTENSITY_TABLE[i] = (1.0f / (PI * (rSquared)) * (INTENSITY_TABLE_RADIUS - i) * INTENSITY_TABLE_RADIUS);
	}
}

void Light::deleteAssets()
{
	delete[] INTENSITY_TABLE;
	INTENSITY_TABLE = nullptr;
}