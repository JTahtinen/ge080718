#include "npc.h"
#include "ai.h"
#include "util.h"

NPC::NPC(float x, float y, const Material* sprite, AI* ai)
	: Actor(x, y, sprite)
	, _ai(ai)
{
}

NPC::NPC(float x, float y, const Material* sprite)
	: Actor(x, y, sprite)
	, _ai(nullptr)
{
}

NPC::NPC(const Vec2& pos)
	: Actor(pos)
	, _ai(nullptr)
{
}

NPC::NPC()
	: Actor()
	, _ai(nullptr)
{
}

void NPC::addHostile(const Actor* actor)
{
	_state.addHostile(actor);
	_state.setMood(ACTIVE);
}

void NPC::setAI(AI* ai)
{
	_ai = ai;
}

void NPC::update(Game* game)
{
	if (_ai)
	{
		_ai->update(this);
	}
	Actor::update(game);
}

NPCState::NPCState()
	: task(NO_TASK)
	, target(nullptr)
	, mood(IDLE)
{
	hostiles.reserve(10);
}

void NPCState::addHostile(const Actor* actor)
{
	util::addToVector(actor, hostiles);
}

void NPCState::setTarget(const Entity* target)
{
	this->target = target;
}

void NPCState::setTask(NPC_Task task)
{
	this->task = task;
}

void NPCState::setMood(NPC_Mood mood)
{
	this->mood = mood;
}

bool NPCState::taskInProgress() const
{
	return task != NO_TASK;
}