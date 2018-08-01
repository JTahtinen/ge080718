#include "uicomponent.h"
#include "globals.h"

UIComponent::UIComponent(float xStart, float yStart, float xEnd, float yEnd, int width, int height)
	: _dimensions(xStart, yStart, xEnd, yEnd)
{
	if (xEnd < xStart)
	{
		float temp = xStart;
		_dimensions.x1 = xEnd;
		_dimensions.x2 = temp;
	}

	if (yEnd < yStart)
	{
		float temp = yStart;
		_dimensions.y1 = yEnd;
		_dimensions.y2 = temp;
	}
	_graphicsComponent = globals::renderer->createGraphicsComponent(width, height);
}

void UIComponent::update(GraphicsComponent* target)
{
	target->render(_graphicsComponent, _dimensions);
}