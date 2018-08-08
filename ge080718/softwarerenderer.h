#pragma once
#include "renderer.h"
#include "surface.h"

class SoftwareWindow;
class Window;

class SoftwareRenderer : public Renderer
{

public:
	SoftwareRenderer();
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target, Effects effects) const override;
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target) const override;
	virtual GraphicsComponent* createGraphicsComponent(int width, int height) const;
};