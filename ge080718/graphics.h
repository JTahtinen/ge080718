#pragma once
#include "surface.h"

class Graphics
{
public:
	unsigned int* getPixelArray(Surface* surface) const;
	void modifySurface(Surface* target, const float* modifierMap) const;
	inline static const Graphics& instance()
	{
		static const Graphics g;
		return g;
	}
private:
	Graphics() {};
};