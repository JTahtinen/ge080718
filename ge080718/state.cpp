#include "state.h"
#include "globals.h"

State::State(const Window* win)
{
	_graphics = globals::renderer->createGraphicsComponent(win->getWidth(), win->getHeight());
}

State::~State()
{
	delete _graphics;
	_graphics = nullptr;
}