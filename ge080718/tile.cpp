#include "tile.h"
#include "graphics.h"
#include "renderer.h"
#include "globals.h"

const int Tile::SIZE = 32;

Tile::Tile(const Material* material , bool barrier)
	: _material(material)
	, _barrier(barrier)
{
}


void Tile::render(int xStart, int yStart, int xEnd, int yEnd, int xOffset, int yOffset, GraphicsComponent* target) const
{
	globals::renderer->renderMaterial(_material, 
		{ (float)xStart, (float)yStart, (float)xEnd, (float)yEnd}, xOffset, yOffset, target);
}

const Material* Tile::getMaterial() const
{
	return _material;
}



