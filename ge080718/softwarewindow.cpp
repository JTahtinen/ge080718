#include "softwarewindow.h"
#include "swgraphicscomponent.h"

SoftwareWindow::SoftwareWindow(int width, int height, const std::string& title)
	: Window(width, height)
{
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_Surface* winSurface = SDL_GetWindowSurface(_window);
}

void SoftwareWindow::update(const GraphicsComponent* graphics)
{
	if (graphics)
	{
		const Surface* renderSource = (Surface*)graphics->getGraphics();
		SDL_BlitScaled(renderSource->_image, NULL, SDL_GetWindowSurface(_window), NULL);
		SDL_UpdateWindowSurface(_window);
	}
}
