#include "graphics.h"

unsigned int* Graphics::getPixelArray(Surface* surface) const
{
	return (unsigned int*)surface->_image->pixels;
}

void Graphics::modifySurface(Surface* target, const float* modifierMap) const
{
	if (!target || !modifierMap)
	{
		return;
	}
	int targetWidth = target->_width;
	unsigned int* pixels = getPixelArray(target);
	for (int y = 0; y < target->_height; ++y)
	{
		for (int x = 0; x < targetWidth; ++x)
		{
			unsigned int originalPixel = pixels[x + y * targetWidth];
			float modifier = modifierMap[x + y * targetWidth];

			unsigned char r = (originalPixel >> 16) & 0xff;
			unsigned char g = (originalPixel >> 8) & 0xff;
			unsigned char b = (originalPixel) & 0xff;

			if ((unsigned int)(r * modifier) > 0xff)
			{
				r = 0xff;
			}
			else
			{
				r = (unsigned char)(r * modifier);
			}

			if ((unsigned int)(g * modifier) > 0xff)
			{
				g = 0xff;
			}
			else
			{
				g = (unsigned char)(g * modifier);
			}
			if ((unsigned int)(b * modifier) > 0xff)
			{
				b = 0xff;
			}
			else
			{
				b = (unsigned char)(b *modifier);
			}
			unsigned int aa = originalPixel & 0xff000000;
			unsigned int rr = r << 16 & 0x00ff0000;
			unsigned int gg = g << 8 & 0x0000ff00;
			unsigned int bb = b & 0x000000ff;

			unsigned int modifiedPixel = aa | rr | gg | bb;
			pixels[x + y * targetWidth] = modifiedPixel;
		}
	}
}