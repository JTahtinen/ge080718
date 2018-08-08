#include "glrenderer.h"
#include "glgraphicscomponent.h"

void GLRenderer::renderMaterial(const Material* material, const Rect& dimensions,
	int xOffset, int yOffset, GraphicsComponent *target, Effects effects) const
{

}

void GLRenderer::renderMaterial(const Material* material, const Rect& dimensions,
	int xOffset, int yOffset, GraphicsComponent *target) const
{
	renderMaterial(material, dimensions, xOffset, yOffset, target, NO_EFFECTS);
}

GraphicsComponent* GLRenderer::createGraphicsComponent(int width, int height) const
{
	return new GLGraphicsComponent(width, height);
}