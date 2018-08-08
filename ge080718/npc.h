#pragma once
#include "actor.h"
#include <vector>

enum NPC_Mood
{
	IDLE = 0, ACTIVE
};

enum NPC_Task
{
	NO_TASK = 0, ATTACK
};

struct NPCState
{
	NPC_Mood							mood;
	const Entity*						target;
	std::vector<const Actor*>			hostiles;
	NPC_Task							task;

	NPCState();
	void addHostile(const Actor* actor);
	void setTarget(const Entity* target);
	void setTask(NPC_Task task);
	void setMood(NPC_Mood mood);
	bool taskInProgress() const;
};

class AI;

class NPC : public Actor
{
	friend class AI;
	NPCState		_state;
	AI*				_ai;
public:
	NPC(float x, float y, const Material* sprite, AI* ai);
	NPC(float x, float y, const Material* sprite);
	NPC(const Vec2& pos);
	NPC();
	virtual void update(Game* game) override;
	void addHostile(const Actor* actor);
	void setAI(AI* ai);
};
