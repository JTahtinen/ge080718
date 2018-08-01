#pragma once
#include "tile.h"
#include <vector>
#include "vec2.h"
#include "camera.h"
#include "light.h"
#include "graphicscomponent.h"
class Map 
{
	std::vector<const Tile*>	_tiles;
	int							_width;
	int							_height;
public:
	~Map();
	void setTile(int x, int y, const Tile* tile);
	void render(GraphicsComponent* target, const Camera* camera) const;
	const Tile* getTile(int x, int y) const;
	const Tile* getTileAtAbsPos(float x, float y) const; 
	static Map* loadMap(const std::string& filepath);
	static Map* createTestMap();
	int getWidthInTiles() const;
	int getHeightInTiles() const;
	int getAbsWidth() const;
	int getAbsHeight() const;
private:
	Map(int width, int height);
};