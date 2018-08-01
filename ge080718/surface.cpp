#include "surface.h"
#include <SDL_image.h>
#include "log.h"
#include "util.h"

Surface::Surface(int width, int height, bool colorkey)
	: _width(width)
	, _height(height)
{
	_image = SDL_CreateRGBSurface(NULL, width, height, 32, 0, 0, 0, 0);
	
	if (colorkey)
	{
		SDL_SetColorKey(_image, 1, SDL_MapRGB(_image->format, 0xff, 0, 0xff));
	}
}

Surface::Surface(int width, int height)
	: Surface(width, height, false)
{
}

Surface::Surface(const Surface& other)
	: Surface(other.getWidth(), other.getHeight())
{
	blit(0, 0, 0, 0, other);
}

Surface::~Surface()
{
	SDL_FreeSurface(_image);
	_image = nullptr;
}

int Surface::getWidth() const
{
	return _width;
}

int Surface::getHeight() const
{
	return _height;
}

void Surface::blit(int xStart, int yStart, int xEnd, int yEnd, const Surface& source)
{
	SDL_Rect dimensions = { xStart, yStart, xEnd - xStart, yEnd - yStart };
	/*int width = (xEnd - xStart);
	int height = (yEnd - yStart);
	float xMod = (float)source._width / (float)width;
	float yMod = (float)source._height / (float)height;

	for (int y = yStart; y < yEnd; ++y)
	{
		for (int x = xStart; x < xEnd; ++x)
		{
			int xSampler = (int)((x - xStart) * xMod);
			int ySampler = (int)((y - yStart) * yMod);
			//unsigned int pixel = (source.getPixel(xSampler, ySampler));
			//if (pixel != 0xff00ff)
			{
				Uint8 r, g, b;
				unsigned int* pixel = (unsigned int*)source._image->pixels + xSampler + ySampler * source._image->w;
				SDL_GetRGB(*pixel, source._image->format, &r, &g, &b);
				drawPoint(x, y, SDL_MapRGB(_image->format, r, g, b));
			}
		}
	}*/
	SDL_BlitScaled(source._image, NULL, _image, &dimensions);
}

void Surface::blit(const Surface& source)
{
	SDL_BlitScaled(source._image, NULL, _image, NULL);
}

Surface* Surface::loadSurface(const std::string& filepath)
{
	Surface* surface = nullptr;
	SDL_Surface* raw_surface = IMG_Load(filepath.c_str());
	if (raw_surface)
	{
		SDL_SetColorKey(raw_surface, 1, 0xff00ff);
		surface = new Surface(raw_surface);
	}
	else
	{
		Log::instance().logAndPrintError("Could not load surface from filepath: " + filepath);
	}
	return surface;
}

Surface::Surface(SDL_Surface* raw_surface)
	: _image(raw_surface)
	, _width(raw_surface->w)
	, _height(raw_surface->h)
{
}