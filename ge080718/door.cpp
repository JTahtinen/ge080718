#include "door.h"
#include "log.h"
#include "globals.h"
#include "testdata.h"

Door::Door(float x, float y, const Material* material, bool open)
	: FixedEntity(x, y, material, !open)
{
}

Door::Door(float x, float y, const Material* material)
	: Door(x, y, material, false)
{
}

void Door::use(Actor* actor)
{
	setBarrier(!_barrier);
	if (this->isOpen())
	{
		Log::msg("Door opened!");
	}
	else {
		Log::msg("Door closed!");
	}
}

bool Door::isOpen() const
{
	return !this->hasBarrier();
}

