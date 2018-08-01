#include "map.h"
#include "testdata.h"
#include "globals.h"

#define WATER 0xffff0000
#define GRASS 0xff00ff00

Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
	_tiles.reserve(width * height);
	for (unsigned int i = 0; i < _tiles.capacity(); ++i)
	{
		_tiles.push_back(TestData::instance().nullTile);
	}
}

Map::~Map()
{
}

void Map::setTile(int x, int y, const Tile* tile)
{
	if (tile && x > -1 && y > -1 && x < _width && y < _height)
	{
		_tiles[x + y * _width] = tile;
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
			int xStart = x * Tile::SIZE;
			int yStart = y * Tile::SIZE;
			int xEnd = xStart + Tile::SIZE;
			int yEnd = yStart + Tile::SIZE;

			_tiles[x + y * _width]->render(xStart, yStart, xEnd, yEnd, (int)camCorr.x, (int)camCorr.y, target);
		}
	}
}

const Tile* Map::getTile(int x, int y) const
{
	if (x > -1 && x < _width && y > -1 && y < _height)
	{
		return _tiles[x + y * _width];
	}
	return TestData::instance().nullTile;
}

const Tile* Map::getTileAtAbsPos(float x, float y) const
{
	int xIndex = (int)(x / Tile::SIZE);
	int yIndex = (int)(y / Tile::SIZE);
	return getTile(xIndex, yIndex);
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
			map->_tiles.push_back(TestData::instance().grassTile);
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