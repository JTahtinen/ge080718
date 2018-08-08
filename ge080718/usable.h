#pragma once
#include "actor.h"

class Usable
{
protected:
	bool			_isTargeted;
public:
	Usable();
	virtual void target(bool value);
	virtual void use(Actor* actor) = 0;
};