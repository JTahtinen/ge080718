#include "renderer.h"
#include "graphics.h"
#include "util.h"

Renderer::Renderer()
{
	_renderableLights.reserve(20);
}

void Renderer::renderSurface(const Surface* source, const Rect& dimensions, Surface* target) const
{
	target->blit((int)dimensions.x1, (int)dimensions.y1, (int)dimensions.x2, (int)dimensions.y2, *source);
}

void Renderer::addRenderableLight(const Light* light)
{
	util::addToVector(light, _renderableLights);
}

void Renderer::clearRenderableLights()
{
	_renderableLights.clear();
}

void Renderer::setAmbientLight(float value)
{
	_ambientLight = value;
}