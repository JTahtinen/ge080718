#pragma once
#include "tile.h"
#include <vector>
#include "vec2.h"
#include "camera.h"
#include "light.h"
#include "fixedentity.h"
#include "graphicscomponent.h"
#include "rect.h"

enum FixedEntityType
{
	DOOR
};

struct Sector
{
	const Tile*					tile;
	std::vector<FixedEntity*>	entities;
};

class Map 
{
	std::vector<Sector>			_sectors;
	int							_width;
	int							_height;
public:
	~Map();
	void setTile(int x, int y, const Tile* tile);
	void render(GraphicsComponent* target, const Camera* camera) const;
	const Tile* getTile(int x, int y) const;
	const Tile* getTileAtAbsPos(float x, float y) const; 
	const Sector* getSector(int x, int y) const;
	const Sector* getSectorAtAbsPos(float x, float y) const;
	static Map* loadMap(const std::string& filepath);
	static Map* createTestMap();
	int getWidthInTiles() const;
	int getHeightInTiles() const;
	int getAbsWidth() const;
	int getAbsHeight() const;
	std::vector<Rect> getSurroundingColliders(float x, float y) const;
	FixedEntity* getEntityFromAbsPos(float x, float y);
	std::vector<FixedEntity*> getEntitiesFromArea(const Vec2& pos, int radius);
private:
	Rect getTilePosOf(float x, float y) const;
	Map(int width, int height);
	void addFixedEntity(int x, int y, FixedEntityType entity);
	void renderSector(int x, int y, int xOffset, int yOffset, GraphicsComponent* target) const;
	bool inBounds(int x, int y) const;
	bool sectorHasBarrier(const Sector* sector) const;
};