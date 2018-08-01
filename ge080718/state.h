#pragma once
#include "window.h"
#include "rect.h"
#include <vector>
#include "graphicscomponent.h"

class State
{
protected:
	GraphicsComponent*			_graphics;
public:
	State(const Window* win);
	~State();
	virtual void update(Window* win) = 0;
};