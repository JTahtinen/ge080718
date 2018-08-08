#pragma once
#include "surface.h"
#include "graphics.h"

namespace sfx
{
	inline void highlight(Surface* surface)
	{
		if (!surface)
			return;

		int width = surface->getWidth();
		int height = surface->getHeight();
		float* buffer = new float[width * height];
		for (int i = 0; i < width * height; ++i)
		{
			buffer[i] = 2.5f;
		}
		const Graphics& g = Graphics::instance();
		g.modifySurface(surface, buffer);
		delete[] buffer;
	}
}