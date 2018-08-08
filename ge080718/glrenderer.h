#pragma once
#include "renderer.h"

class GLRenderer : public Renderer
{
public:
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target, Effects effects) const override;
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target) const override;
	virtual GraphicsComponent* createGraphicsComponent(int width, int height) const;
};