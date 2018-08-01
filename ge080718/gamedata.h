#pragma once
#include "map.h"
#include "worldobject.h"
#include "actor.h"
#include "player.h"
#include "light.h"

struct GameData
{

	Map*						map;
	std::vector<Entity*>		entities;
	std::vector<WorldObject*>	worldObjects;
	std::vector<Actor*>			actors;
	std::vector<Light*>			lights;
	Player*						player;

public:
	GameData();
	~GameData();
	void setMap(Map* map);
	void addEntity(Entity* entity);
	void addWorldObject(WorldObject* worldObject);
	void addActor(Actor* actor);
	void addLight(Light* light);
	void setPlayer(Player* player);
private:
	template <typename T>
	static void add(T* entity, std::vector<T*>& entities);
};