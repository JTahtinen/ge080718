#include "map.h"
#include "testdata.h"
#include "globals.h"
#include "door.h"
#include "worldObject.h"

#define WATER 0xffff0000
#define GRASS 0xff00ff00

Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
	_sectors.reserve(width * height);
	for (unsigned int i = 0; i < _sectors.capacity(); ++i)
	{
		_sectors.push_back(Sector());
		_sectors[i].tile = TestData::instance().nullTile;
	}
}

Map::~Map()
{
}

void Map::setTile(int x, int y, const Tile* tile)
{
	if (inBounds(x, y))
	{
		_sectors[x + y * _width].tile = tile;
	}
}

void Map::render(GraphicsComponent* target, const Camera* camera) const
{
	int targetWidth = target->getWidth();
	int targetHeight = target->getHeight();
	const Vec2 camCorr = camera->getCameraCorrection();
	int xStart = (int)((-camCorr.x) / Tile::SIZE);
	int yStart = (int)((-camCorr.y) / Tile::SIZE);
	int xEnd = xStart + (targetWidth / Tile::SIZE) + 2;
	int yEnd = yStart + (targetHeight / Tile::SIZE) + 2;

	if (xStart < 0)
	{
		xStart = 0;
	}
	else if (xStart > _width)
	{
		return;
	}

	if (yStart < 0)
	{
		yStart = 0;
	}
	else if (yStart > _height)
	{
		return;
	}

	if (xEnd > _width)
	{
		xEnd = _width;
	}
	else if (xEnd < 0)
	{
		return;
	}

	if (yEnd > _height)
	{
		yEnd = _height;
	}
	else if (yEnd < 0)
	{
		return;
	}

	for (int y = yStart; y < yEnd; ++y)
	{
		for (int x = xStart; x < xEnd; ++x)
		{
			
			renderSector(x, y, (int)camCorr.x, (int)camCorr.y, target);
			//_tiles[x + y * _width]->render(xStart, yStart, xEnd, yEnd, (int)camCorr.x, (int)camCorr.y, target);
		}
	}
}

void Map::renderSector(int x, int y, int xOffset, int yOffset, GraphicsComponent* target) const
{
	int xStart = x * Tile::SIZE;
	int yStart = y * Tile::SIZE;
	int xEnd = xStart + Tile::SIZE;
	int yEnd = yStart + Tile::SIZE;
	const Sector* sector = &_sectors[x + y * _width];
	if (!sector->entities.empty())
	{
		sector->entities.back()->render(xStart, yStart, xEnd, yEnd, xOffset, yOffset, target);
	}
	else
	{
		sector->tile->render(xStart, yStart, xEnd, yEnd, xOffset, yOffset, target);
	}
}

const Tile* Map::getTile(int x, int y) const
{
	return (getSector(x, y)->tile);
}

const Tile* Map::getTileAtAbsPos(float x, float y) const
{
	return (getSectorAtAbsPos(x, y)->tile);
}

const Sector* Map::getSector(int x, int y) const
{
	if (inBounds(x, y))
	{
		return &_sectors[x + y * _width];
	}
	return nullptr;
}

const Sector* Map::getSectorAtAbsPos(float x, float y) const
{
	int xIndex = (int)(x / Tile::SIZE);
	int yIndex = (int)(y / Tile::SIZE);
	return getSector(xIndex, yIndex);
}

Map* Map::loadMap(const std::string& filepath)
{
	Surface* mapImage = Surface::loadSurface(filepath);
	if (!mapImage)
	{
		Log::err("Could not load map: " + filepath);
		return nullptr;
	}
	int width = mapImage->getWidth();
	int height = mapImage->getHeight();
	Map* map = new Map(width, height);
	unsigned int* pixels = (unsigned int*)mapImage->_image->pixels;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Tile* tile;
			unsigned int pixel = pixels[x + y * width];
			switch (pixel)
			{
			case GRASS:
				tile = TestData::instance().grassTile;
				break;
			case WATER:
				tile = TestData::instance().waterTile;
				break;
			default:
				tile = TestData::instance().grassTile;
				break;
			}
			map->setTile(x, y, tile);
		}
	}
	map->addFixedEntity(14, 7, new Door(TestData::instance().waterMat));
	delete mapImage;
	return map;
}

Map* Map::createTestMap()
{
	int width = 40;
	int height = 40;
	Map* map = new Map(width, height);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			map->_sectors[x + y * width].tile = TestData::instance().grassTile;
		}
	}

	for (int y = 10; y < 20; ++y)
	{
		for (int x = 10; x < 20; ++x)
		{
			map->setTile(x, y, TestData::instance().waterTile);
		}
	}
	return map;
}

int Map::getWidthInTiles() const
{
	return _width;
}

int Map::getHeightInTiles() const
{
	return _height;
}

int Map::getAbsWidth() const
{
	return _width * Tile::SIZE;
}

int Map::getAbsHeight() const
{
	return _height * Tile::SIZE;
}

void Map::activateSector(int x, int y)
{
	if (inBounds(x, y))
	{
		std::vector<FixedEntity*>& entities = _sectors[x + y * _width].entities;
		if (!entities.empty())
		{
			_sectors[x + y * _width].entities.back()->use();
		}
	}
}

void Map::activateSectorAtAbsPos(float x, float y)
{
	int xIndex = (int)(x / Tile::SIZE);
	int yIndex = (int)(y / Tile::SIZE);
	activateSector(xIndex, yIndex);
}

void Map::addFixedEntity(int x, int y, FixedEntity* entity)
{
	if (entity)
	{
		if (inBounds(x, y))
		{
			_sectors[x + y * _width].entities.push_back(entity);
		}
		else {
			Log::err("Removed fixed entity - Out of bounds!");
			delete entity;
		}
	}
}

std::vector<Rect> Map::getSurroundingColliders(float x, float y) const
{
	std::vector<Rect> rects;
	rects.reserve(8);

	const Sector* topLeft = getSectorAtAbsPos(x - 32, y - 32);
	const Sector* topUp = getSectorAtAbsPos(x, y - 32);
	const Sector* topRight = getSectorAtAbsPos(x + 32, y - 32);
	const Sector* midLeft = getSectorAtAbsPos(x - 32, y);
	const Sector* midRight = getSectorAtAbsPos(x + 32, y);
	const Sector* bottomLeft = getSectorAtAbsPos(x - 32, y + 32);
	const Sector* bottomDown = getSectorAtAbsPos(x, y + 32);
	const Sector* bottomRight = getSectorAtAbsPos(x + 32, y + 32);

	if (sectorHasBarrier(topLeft))			rects.emplace_back(getTilePosOf(x - 32, y - 32));
	if (sectorHasBarrier(topUp))			rects.emplace_back(getTilePosOf(x, y - 32));
	if (sectorHasBarrier(topRight))			rects.emplace_back(getTilePosOf(x + 32, y - 32));
	if (sectorHasBarrier(midLeft))			rects.emplace_back(getTilePosOf(x - 32, y));
	if (sectorHasBarrier(midRight))			rects.emplace_back(getTilePosOf(x + 32, y));
	if (sectorHasBarrier(bottomLeft))		rects.emplace_back(getTilePosOf(x - 32, y + 32));
	if (sectorHasBarrier(bottomDown))		rects.emplace_back(getTilePosOf(x, y + 32));
	if (sectorHasBarrier(bottomRight))		rects.emplace_back(getTilePosOf(x + 32, y + 32));
	
	return rects;
}

bool Map::inBounds(int x, int y) const
{
	return (math::inBounds((float)x, (float)y, 0, 0, (float)_width, (float)_height));
}

Rect Map::getTilePosOf(float x, float y) const
{
	int tileX = (int)x / Tile::SIZE * Tile::SIZE - Tile::SIZE / 2; 
	int tileY = (int)y / Tile::SIZE * Tile::SIZE - Tile::SIZE / 2;
	
	return Rect((float)tileX, (float)tileY, (float)tileX + Tile::SIZE, (float)tileY + Tile::SIZE);
}

bool Map::sectorHasBarrier(const Sector* sector) const
{
	if (sector)
	{
		if (sector->tile->hasBarrier())
		{
			return true;
		}
		for (unsigned int i = 0; i < sector->entities.size(); ++i)
		{
			if (sector->entities[i]->hasBarrier())
			{
				return true;
			}
		}
	}
	return false;
}

FixedEntity* Map::getEntityFromAbsPos(float x, float y)
{
	int xIndex = (int)x / Tile::SIZE;
	int yIndex = (int)y / Tile::SIZE;
	if (inBounds(xIndex, yIndex))
	{
		Sector* sector = &_sectors[xIndex + yIndex * _width];
		if (sector->entities.size() > 0)
		{
			return sector->entities.back();
		}
	}
	return nullptr;
}