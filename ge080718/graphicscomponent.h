#pragma once
#include "rect.h"
#include <string>

class UIComponent;

class GraphicsComponent
{
public:
	GraphicsComponent();
	virtual const void* getGraphics() const = 0;
	virtual void render(GraphicsComponent* source, const Rect& dimensions) const = 0;
	virtual void render(GraphicsComponent* source, int xStart, int yStart, int xEnd, int yEnd) = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual void drawPoint(int x, int y, unsigned int color) = 0;
	virtual void modifyPoint(int x, int y, float value) = 0;
	virtual void clear(unsigned int color) = 0;
	virtual void drawRect(int xStart, int yStart, int xEnd, int yEnd, unsigned int color) = 0;
	virtual void applyGraphicsComponent(int xStart, int yStart, int xEnd, int yEnd, const GraphicsComponent& source) = 0;
	virtual void applyGraphicsComponent(const GraphicsComponent& source) = 0;
	static GraphicsComponent* loadGraphicsComponent(const std::string& filepath);
};