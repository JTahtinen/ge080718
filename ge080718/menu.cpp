#include "menu.h"

Menu::Menu(const Window* win)
	: State(win)
{
}

void Menu::update(Window* win)
{
	_graphics->clear(0xff0000);
	win->update(_graphics);
}