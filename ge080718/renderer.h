#pragma once
#include "material.h"
#include "light.h"
#include "rect.h"
#include <vector>

enum RendererType
{
	SOFTWARE, OPENGL
};

enum Effects
{
	NO_EFFECTS	= 0,
	HIGHLIGHT	= 1 << 0,
};

class Renderer
{
protected:

	float							_ambientLight;
	std::vector<const Light*>		_renderableLights;

public:
	Renderer();
	void renderSurface(const Surface* source, const Rect& dimensions, Surface *target) const;
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target, Effects effects) const = 0;
	virtual void renderMaterial(const Material* material, const Rect& dimensions,
		int xOffset, int yOffset, GraphicsComponent *target) const = 0;
	/*inline static Renderer& instance()
	{
		static Renderer renderer;
		return renderer;
	}*/
	void addRenderableLight(const Light* light);
	void clearRenderableLights();
	void setAmbientLight(float value);
	virtual GraphicsComponent* createGraphicsComponent(int width, int height) const = 0;
};