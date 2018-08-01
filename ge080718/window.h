#pragma once
#include <SDL.h>
#include <string>
#include "graphicscomponent.h"

class Window
{
protected:
	SDL_Window*			_window;
	int					_width;
	int					_height;
public:
	Window(int width, int height);
	~Window();
	int getWidth() const;
	int getHeight() const;
	virtual void update(const GraphicsComponent* graphics) = 0;
};