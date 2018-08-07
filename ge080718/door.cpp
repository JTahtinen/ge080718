#include "door.h"
#include "log.h"

Door::Door(const Material* material, bool open)
	: FixedEntity(material, !open)
{

}

Door::Door(const Material* material)
	: Door(material, false)
{
}

void Door::use()
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

void Door::target()
{
	Log::msg("Door targeted!");
}

bool Door::isOpen() const
{
	return !this->hasBarrier();
}