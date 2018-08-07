#include "fixedentity.h"
#include "globals.h"

FixedEntity::FixedEntity(const Material* material, bool barrier)
	: _material(material)
	, _barrier(barrier)
{

}

FixedEntity::FixedEntity(const Material* material)
	: FixedEntity(material, true)
{

}

void FixedEntity::setBarrier(bool value)
{
	_barrier = value;
}

bool FixedEntity::hasBarrier() const
{
	return _barrier;
}

void FixedEntity::render(int xStart, int yStart, int xEnd, int yEnd, int xOffset, int yOffset, GraphicsComponent* target) const
{
	globals::renderer->renderMaterial(_material, { (float)xStart, (float)yStart, (float)xEnd, (float)yEnd}, xOffset, yOffset, target);
}