#include "glgraphicscomponent.h"

GLGraphicsComponent::GLGraphicsComponent(int width, int height)
	: GraphicsComponent()
{

}

const void* GLGraphicsComponent::getGraphics() const
{
	return nullptr;
}

void GLGraphicsComponent::render(GraphicsComponent* target, const Rect& dimensions) const
{

}

void GLGraphicsComponent::render(GraphicsComponent* target, int xStart, int yStart, int xEnd, int yEnd)
{

}

int GLGraphicsComponent::getWidth() const
{
	return 0;
}

int GLGraphicsComponent::getHeight() const
{
	return 0;
}

void GLGraphicsComponent::drawPoint(int x, int y, unsigned int color)
{

}

void GLGraphicsComponent::modifyPoint(int x, int y, float value)
{

}

void GLGraphicsComponent::clear(unsigned int color)
{

}

void GLGraphicsComponent::drawRect(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
{

}

void GLGraphicsComponent::applyGraphicsComponent(int xStart, int yStart, int xEnd, int yEnd, const GraphicsComponent& source)
{

}

void GLGraphicsComponent::applyGraphicsComponent(const GraphicsComponent& source)
{

}