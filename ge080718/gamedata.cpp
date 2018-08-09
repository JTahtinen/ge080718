#include "gamedata.h"
#include "log.h"
#include "util.h"

GameData::GameData()
	: player(nullptr)
	, map(nullptr)
	, camera(nullptr)
{
	entities.reserve(100);
	lights.reserve(50);
	actors.reserve(50);
	worldObjects.reserve(50);
	npcs.reserve(50);
}

GameData::~GameData()
{
	delete map;
	map = nullptr;
	unsigned int i;
	for (i = 0; i < entities.size(); ++i)
	{
		delete entities[i];
		entities[i] = nullptr;
	}
}

void GameData::setCamera(Camera* camera)
{
	if (camera)
	{
		this->camera = camera;
		addEntity(camera);
	}
}

void GameData::setMap(Map* map)
{
	this->map = map;
}

void GameData::addEntity(Entity* entity)
{
	add(entity, entities);
}

void GameData::setPlayer(Player* player)
{
	if (player)
	{
		if (!this->player)
		{
			this->player = player;
			addActor(player);
			return;
		}
		Player* oldPlayer = this->player;
		this->player = player;
		for (unsigned int i = 0; i < entities.size(); ++i)
		{
			if (entities[i] == this->player) {
				entities[i] = player;
				for (unsigned int j = 0; j < actors.size(); ++j)
				{
					if (actors[j] == oldPlayer)
					{
						actors[j] = player;
						return;
					}
				}
				addActor(player);
				return;
			}
		}
		addActor(player);
	}
}

void GameData::addWorldObject(WorldObject* worldObject)
{
	add(worldObject, worldObjects);
	addEntity(worldObject);
}

void GameData::addNPC(NPC* npc)
{
	add(npc, npcs);
	addActor(npc);
}

void GameData::addActor(Actor* actor)
{
	add(actor, actors);
	addEntity(actor);
}

void GameData::addLight(Light* light)
{
	add(light, lights);
	addEntity(light);
}

template <typename T>
void GameData::add(T* entity, std::vector<T*>& entities)
{
	util::addToVector(entity, entities);
}