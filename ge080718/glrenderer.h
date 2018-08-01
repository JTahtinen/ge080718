#pragma once
#include "renderer.h"

class GLRenderer : public Renderer
{
public:
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target) const;
	virtual GraphicsComponent* createGraphicsComponent(int width, int height) const;
};