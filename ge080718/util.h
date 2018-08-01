#pragma once
#include <string>
#include "surface.h"
#include <vector>
#include "globals.h"

namespace util
{
	template <typename T>
	inline void clearBuffer(T* buffer, int width, int height)
	{
		for (int i = 0; i < width * height; ++i)
		{
			buffer[i] = 0;
		}
	}

	template <typename T>
	inline void fillBuffer(T* buffer, int width, int height, T value)
	{
		for (int i = 0; i < width * height; ++i)
		{
			buffer[i] = value;
		}
	}

	template <typename T>
	inline void modifyBuffer(T* buffer, int width, int height, float modifier)
	{
		for (int i = 0; i < width * height; ++i)
		{
			buffer[i] *= modifier;
		}
	}

	template <typename T>
	inline void addToVector(T* object, std::vector<T*>& vector)
	{
		if (object)
		{
			for (unsigned int i = 0; i < vector.size(); ++i)
			{
				if (vector[i] == object)
				{
					Log::err("Object already in vector!");
					return;
				}
			}
			vector.push_back(object);
		}
	}

	inline unsigned int reverseBytes(unsigned int source)
	{
		unsigned int b1 = source << 24 & 0xff000000;
		unsigned int b2 = source << 8 & 0x00ff0000;
		unsigned int b3 = source >> 8 & 0x0000ff00;
		unsigned int b4 = source >> 24 & 0x000000ff;
		return (b1 | b2 | b3 | b4);
	}

	inline unsigned int lastByteFirst(unsigned int source)
	{
		unsigned int b1 = source >> 8  & 0x00ffffff;
		unsigned int b2 = source << 24 & 0xff000000;
		return (b1 | b2);
	}
}
