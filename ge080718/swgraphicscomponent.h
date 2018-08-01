#pragma once
#include "graphicscomponent.h"
#include "surface.h"
#include "rect.h"
class SWGraphicsComponent : public GraphicsComponent
{
	Surface*		_graphics;
public:
	SWGraphicsComponent(int width, int height);
	SWGraphicsComponent(Surface* surface);
	~SWGraphicsComponent();
	virtual const void* getGraphics() const;
	const Surface* getSurface() const;
	virtual void render(GraphicsComponent* source, const Rect& dimensions) const;
	virtual void render(GraphicsComponent* source, int xStart, int yStart, int xEnd, int yEnd);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual inline void drawPoint(int x, int y, unsigned int color)
	{
		_graphics->drawPoint(x, y, color);
	}
	
	virtual inline void modifyPoint(int x, int y, float value)
	{
		_graphics->modifyPoint(x, y, value);
	}

	virtual inline void clear(unsigned int color)
	{
		_graphics->clear(color);
	}
	virtual inline void drawRect(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
	{
		_graphics->drawRect(xStart, yStart, xEnd, yEnd, color);
	}
	virtual inline void applyGraphicsComponent(int xStart, int yStart, int xEnd, int yEnd, const GraphicsComponent& source)
	{
		_graphics->blit(xStart, yStart, xEnd, yEnd, *(Surface*)source.getGraphics());
	}

	virtual inline void applyGraphicsComponent(const GraphicsComponent& source)
	{
		_graphics->blit(*(Surface*)source.getGraphics());
	}

	static SWGraphicsComponent* loadGraphicsComponent(const std::string& filepath);
};