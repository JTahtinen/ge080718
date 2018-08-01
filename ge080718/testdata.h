#pragma once
#include "surfacepool.h"
#include "tile.h"
#include "material.h"

struct TestData
{
	GraphicsPool* surfaces;
	int grassSurface;
	int actorSurface;
	int waterSurface;
	int backgroundSurface;
	int defaultSurface;
	int dudeSurface;

	Material* grassMat;
	Material* waterMat;
	Material* nullMat;
	Material* dudeMat;

	Tile* grassTile;
	Tile* waterTile;
	Tile* nullTile;

	TestData();
	~TestData();
	inline static TestData& instance()
	{
		static TestData data;
		return data;
	}
};