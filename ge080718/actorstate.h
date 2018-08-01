#pragma once
#include <vector>

enum Actor_Mood
{
	IDLE = 0, ACTIVE
};

enum Actor_Task
{
	NO_TASK = 0, ATTACK
};

class Actor;
class Entity;

struct ActorState
{
	Actor_Mood							mood;
	const Entity*						target;
	std::vector<const Actor*>			hostiles;
	Actor_Task							task;

	ActorState();
	void addHostile(const Actor* actor);
	void setTarget(const Entity* target);
	void setTask(Actor_Task task);
	void setMood(Actor_Mood mood);
	bool taskInProgress() const;
};