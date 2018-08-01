#pragma once
#include "state.h"

class Menu : public State
{
public:
	Menu(const Window* win);
	virtual void update(Window* win);
};