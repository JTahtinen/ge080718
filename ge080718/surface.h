#pragma once
#include <SDL.h>
#include <string>

struct Surface
{
	friend class Window;

	SDL_Surface*	_image;
	int				_width;
	int				_height;

	Surface(int width, int height, bool colorkey);
	Surface(int width, int height);
	Surface(const Surface& other);
	~Surface();
	int getWidth() const;
	int getHeight() const;
	void blit(int xStart, int yStart, int xEnd, int yEnd, const Surface& source);
	void blit(const Surface& source);

	inline void drawPoint(int x, int y, unsigned int color)
	{
		unsigned int* pixels = (unsigned int*)_image->pixels;
		*(pixels + x + y * _width) = color;
	}

	inline void drawRect(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
	{
		for (int y = 0; y < yEnd - yStart; ++y)
		{
		for (int x = 0; x < xEnd - xStart; ++x)
			{
				drawPoint(xStart + x, yStart + y, color);
			}
		}
	}

	inline void clear(unsigned int color)
	{
		drawRect(0, 0, _width, _height, color);
	}

	inline void modifyPoint(int x, int y, float value)
	{
		unsigned int originalPixel = getPixel(x, y);

		unsigned char r = (originalPixel >> 16) & 0xff;
		unsigned char g = (originalPixel >> 8) & 0xff;
		unsigned char b = (originalPixel) & 0xff;

		if ((unsigned int)(r * value) > 0xff)
		{
			r = 0xff;
		}
		else
		{
			r = (unsigned char)(r * value);
		}

		if ((unsigned int)(g * value) > 0xff)
		{
			g = 0xff;
		}
		else
		{
			g = (unsigned char)(g * value);
		}		
		if ((unsigned int)(b * value) > 0xff)
		{
			b = 0xff;
		}
		else
		{
			b = (unsigned char)(b *value);
		}
		unsigned int aa =			originalPixel & 0xff000000;
		unsigned int rr =			r << 16 & 0x00ff0000;
		unsigned int gg =			g << 8  & 0x0000ff00;
		unsigned int bb =			     b  & 0x000000ff;

		unsigned int modifiedPixel = aa | rr | gg | bb;
		drawPoint(x, y, modifiedPixel);
	}

	static Surface* loadSurface(const std::string& filepath);
private:
	inline unsigned int getPixel(int x, int y) const
	{
		if (x > -1 && y > -1 && x < _width && y < _height)
		{
			unsigned int* pixels = (unsigned int*)_image->pixels;
			return pixels[x + y * _width];
		}
		return 0;
	}
	
	Surface(SDL_Surface* raw_surface);
};
