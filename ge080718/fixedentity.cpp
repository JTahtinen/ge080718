#include "fixedentity.h"
#include "globals.h"
#include "testdata.h"

FixedEntity::FixedEntity(float x, float y, const Material* material, bool barrier)
	: Entity(x, y)
	, _material(material)
	, _barrier(barrier)
{
}

FixedEntity::FixedEntity(float x, float y, const Material* material)
	: FixedEntity(x, y, material, true)
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
	if (this->_isTargeted)
	{
		globals::renderer->renderMaterial(_material, { (float)xStart, (float)yStart, (float)xEnd, (float)yEnd }, xOffset, yOffset, target, HIGHLIGHT);
	}
	else 
	{
		globals::renderer->renderMaterial(_material, { (float)xStart, (float)yStart, (float)xEnd, (float)yEnd }, xOffset, yOffset, target);
	}
}