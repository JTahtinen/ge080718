#include "usable.h"
#include "log.h"

Usable::Usable()
	: _isTargeted(false)
{
}

void Usable::target(bool value)
{
	_isTargeted = value;
	if (_isTargeted)
		Log::msg("Usable entity targeted!");
}