#include "window.h"
#include "globals.h"

Window::Window(int width, int height)
	: _width(width)
	, _height(height)
{
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	_window = nullptr;
}

int Window::getWidth() const
{
	return _width;
}

int Window::getHeight() const
{
	return _height;
}