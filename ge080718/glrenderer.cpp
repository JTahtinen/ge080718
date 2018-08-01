#include "glrenderer.h"
#include "glgraphicscomponent.h"

void GLRenderer::renderMaterial(const Material* material, const Rect& dimensions,
	int xOffset, int yOffset, GraphicsComponent *target) const
{

}

GraphicsComponent* GLRenderer::createGraphicsComponent(int width, int height) const
{
	return new GLGraphicsComponent(width, height);
}