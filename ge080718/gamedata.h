#pragma once
#include "map.h"
#include "worldobject.h"
#include "actor.h"
#include "player.h"
#include "light.h"
#include "npc.h"
#include "camera.h"

class GameData
{
public:
	Map*						map;
	Camera*						camera;
	std::vector<Entity*>		entities;
	std::vector<WorldObject*>	worldObjects;
	std::vector<Actor*>			actors;
	std::vector<NPC*>			npcs;
	std::vector<Light*>			lights;
	Player*						player;

public:
	GameData();
	~GameData();
	void setCamera(Camera* camera);
	void setMap(Map* map);
	void addEntity(Entity* entity);
	void addWorldObject(WorldObject* worldObject);
	void addNPC(NPC* npc);
	void addActor(Actor* actor);
	void addLight(Light* light);
	void setPlayer(Player* player);
private:
	template <typename T>
	static void add(T* entity, std::vector<T*>& entities);
};