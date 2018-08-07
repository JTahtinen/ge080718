#pragma once
#include "material.h"
#include "vec2.h"
#include "usable.h"

class Map;

class FixedEntity : public Usable
{
protected:
	bool				_barrier;
	const Material*		_material;
public:
	FixedEntity(const Material* material, bool barrier);
	FixedEntity(const Material* material);
	void setBarrier(bool value);
	bool hasBarrier() const;
	void render(int xStart, int yStart, int xEnd, int yEnd, int xOffset, int yOffset, GraphicsComponent* target) const;
};