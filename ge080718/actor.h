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

class ActorTaskList
{
	std::vector<ActorTask> _tasks;
public:
	ActorTaskList() { _tasks.reserve(10); }
	void push(ActorTask task);
	ActorTask pop();
	void clear();
	unsigned int getSize() const;
};

class Actor : public WorldObject
{
protected:
	ActorWorldData				_worldData;
	ActorTaskList				_movementTasks;
	ActorTaskList				_actionTasks;
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
	void handleMovementTasks();
	void handleActionTasks();
	void targetEntity(Usable* entity);
	void updateWorldData(Game* game);
protected:
	void pushTask(ActorTask task);
};


enum ActorTask
{
	NULL_TASK,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SWITCH_TARGET,
	ACTIVATE_TARGET,
	SEEK_TARGET
};