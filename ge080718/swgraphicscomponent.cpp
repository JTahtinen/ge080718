#include "swgraphicscomponent.h"
#include "uicomponent.h"
#include <SDL_image.h>

SWGraphicsComponent::SWGraphicsComponent(int width, int height)
{
	_graphics = new Surface(width, height);
}

SWGraphicsComponent::SWGraphicsComponent(Surface* surface)
{
	_graphics = surface;
}

SWGraphicsComponent::~SWGraphicsComponent()
{
	delete _graphics;
	_graphics = nullptr;
}

const void* SWGraphicsComponent::getGraphics() const
{
	return getSurface();
}

const Surface* SWGraphicsComponent::getSurface() const
{
	return _graphics;
}

void SWGraphicsComponent::render(GraphicsComponent* target, const Rect& dimensions) const
{
	if (target) {
		int targetHalfWidth = _graphics->getWidth() / 2;
		int targetHalfHeight = _graphics->getHeight() / 2;

		int targetXStart	= (int)(dimensions.x1 * targetHalfWidth + targetHalfWidth);
		int targetYStart	= (int)(dimensions.y1 * targetHalfHeight + targetHalfHeight);
		int targetXEnd		= (int)(dimensions.x2 * targetHalfWidth + targetHalfWidth);
		int targetYEnd		= (int)(dimensions.y2 * targetHalfHeight + targetHalfHeight);
		const Surface* targetSurface = (Surface*)target->getGraphics();
		_graphics->blit(targetXStart, targetYStart, targetXEnd, targetYEnd, *targetSurface);
	}
}

void SWGraphicsComponent::render(GraphicsComponent* target, int xStart, int yStart, int xEnd, int yEnd)
{
	if (target) {
		const Surface* targetSurface = (Surface*)target->getGraphics();
		_graphics->blit(xStart, yStart, xEnd, yEnd, *targetSurface);
	}
}

int SWGraphicsComponent::getWidth() const
{
	return _graphics->_width;
}

int SWGraphicsComponent::getHeight() const
{
	return _graphics->_height;
}

SWGraphicsComponent* SWGraphicsComponent::loadGraphicsComponent(const std::string& filepath)
{
	Surface* surface = Surface::loadSurface(filepath);
	if (surface)
	{
		return new SWGraphicsComponent(surface);
	}
	return nullptr;
}