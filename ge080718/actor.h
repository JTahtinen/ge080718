#pragma once
#include "worldobject.h"
#include "vec2.h"
#include "surface.h"

class FixedEntity;
class Usable;
enum ActorTask;

struct ActorWorldData
{
	std::vector<FixedEntity*>		potentialTargets;
	std::vector<Entity*>			nearbyEntities;
};

class Actor : public WorldObject
{
	friend class AI;
protected:
	ActorWorldData				_worldData;
	std::vector<ActorTask>		_tasks;
	Usable*						_target;
	float						_speed;
public:
	Actor(float x, float y, const Material* sprite);
	Actor(const Vec2& pos);
	Actor();
	virtual void update(Game* game) override;
	void move(const Vec2& dir, float speed);
private:
	void selectClosestTarget();
	void selectNextTarget();
	void handleTasks();
	void targetEntity(Usable* entity);
	void updateWorldData(Game* game);
protected:
	void pushTask(ActorTask task);
};


enum ActorTask
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SWITCH_TARGET,
	ACTIVATE_TARGET,
	SEEK_TARGET
};