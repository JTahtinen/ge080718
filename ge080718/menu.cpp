#include "menu.h"

Menu::Menu(const Window* win)
	: State(win)
{
}

void Menu::update(Window* win, float frameTime)
{
	_graphics->clear(0xff0000);
	win->update(_graphics);
}