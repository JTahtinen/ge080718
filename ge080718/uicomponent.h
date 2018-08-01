#pragma once
#include "surface.h"
#include "graphicscomponent.h"
#include "window.h"

class UIComponent
{
	friend class GraphicsComponent;
protected:
	GraphicsComponent*		_graphicsComponent;
	Rect					_dimensions;
public:
	UIComponent(float xStart, float yStart, float xEnd, float yEnd, int width, int height);
	virtual void update(GraphicsComponent* target);
};