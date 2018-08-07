#pragma once
#include "material.h"
#include "light.h"
#include <vector>
#include "graphicscomponent.h"

class Tile
{
protected:
	const Material*			_material;
	bool					_barrier;
public:
	static const int		SIZE;

	Tile(const Material* material, bool barrier);
	void render(int xStart, int yStart, int xEnd, int yEnd, int xOffset, int yOffset, GraphicsComponent* target) const;
	const Material* getMaterial() const;
	bool hasBarrier() const;
};


