#pragma once
#include "graphicscomponent.h"

class GLGraphicsComponent : public GraphicsComponent
{
public:
	GLGraphicsComponent(int width, int height);
	virtual const void* getGraphics() const;
	virtual void render(GraphicsComponent* target, const Rect& dimensions) const;
	virtual void render(GraphicsComponent* target, int xStart, int yStart, int xEnd, int yEnd);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual void drawPoint(int x, int y, unsigned int color);
	virtual void modifyPoint(int x, int y, float value);
	virtual void clear(unsigned int color);
	virtual void drawRect(int xStart, int yStart, int xEnd, int yEnd, unsigned int color);
	virtual void applyGraphicsComponent(int xStart, int yStart, int xEnd, int yEnd, const GraphicsComponent& source) ;
	virtual void applyGraphicsComponent(const GraphicsComponent& source);
	
};