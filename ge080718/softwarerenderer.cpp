#include "softwarerenderer.h"
#include "util.h"
#include "graphics.h"
#include "SoftwareWindow.h"
#include "swgraphicscomponent.h"

SoftwareRenderer::SoftwareRenderer()
{
}

void SoftwareRenderer::renderMaterial(const Material* material, const Rect& dimensions,
	int xOffset, int yOffset, GraphicsComponent *target) const
{
	if (dimensions.x2 <= dimensions.x1 || dimensions.y2 <= dimensions.y1)
	{
		return;
	}

	int width = (int)(dimensions.x2 - dimensions.x1);
	int height = (int)(dimensions.y2 - dimensions.y1);
	SWGraphicsComponent* finalSurface = new SWGraphicsComponent(width, height);
	finalSurface->render(material->texture, 0, 0, width, height);
	
	float* lightBuffer = new float[width * height];

	util::fillBuffer(lightBuffer, width, height, _ambientLight);
	Vec2 screenPos = Vec2(dimensions.x1, dimensions.y1);
	for (unsigned int i = 0; i < _renderableLights.size(); ++i)
	{
		const Light* light = _renderableLights[i];
		Vec2 topLeft(dimensions.x1, dimensions.y1);
		Vec2 topRight(dimensions.x2, dimensions.y1);
		Vec2 bottomLeft(dimensions.x1, dimensions.y2);
		Vec2 bottomRight(dimensions.x2, dimensions.y2);
		if (light->isInRadiusOf(topLeft)
			|| light->isInRadiusOf(topRight)
			|| light->isInRadiusOf(bottomLeft)
			|| light->isInRadiusOf(bottomRight))
		{
			_renderableLights[i]->render(lightBuffer, width, height, screenPos);
		}
	}
	util::modifyBuffer(lightBuffer, width, height, material->specular);
	const Graphics& g = Graphics::instance();
	Surface* fSurface = (Surface*)finalSurface->getGraphics();
	g.modifySurface(fSurface, lightBuffer);
	target->render(finalSurface, (int)(dimensions.x1 + xOffset), (int)(dimensions.y1 + yOffset), (int)(dimensions.x2 + xOffset), (int)(dimensions.y2 + yOffset));
	delete finalSurface;
	delete[] lightBuffer;

}


GraphicsComponent* SoftwareRenderer::createGraphicsComponent(int width, int height) const
{
	return new SWGraphicsComponent(width, height);
}