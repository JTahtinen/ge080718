#pragma once
#include "material.h"
#include "vec2.h"
#include "usable.h"

class Map;

class FixedEntity : public Entity, public Usable
{
protected:
	bool				_barrier;
	const Material*		_material;
public:
	FixedEntity(float x, float y, const Material* material, bool barrier);
	FixedEntity(float x, float y, const Material* material);
	void setBarrier(bool value);
	bool hasBarrier() const;
	virtual void render(int xStart, int yStart, int xEnd, int yEnd, int xOffset, int yOffset, GraphicsComponent* target) const;
};