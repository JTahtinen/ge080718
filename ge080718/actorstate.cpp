#include "actorstate.h"
#include "util.h"

ActorState::ActorState()
	: task(NO_TASK)
	, target(nullptr)
	, mood(IDLE)
{
	hostiles.reserve(10);
}

void ActorState::addHostile(const Actor* actor)
{
	util::addToVector(actor, hostiles);
}

void ActorState::setTarget(const Entity* target)
{
	this->target = target;
}

void ActorState::setTask(Actor_Task task)
{
	this->task = task;
}

void ActorState::setMood(Actor_Mood mood)
{
	this->mood = mood;
}

bool ActorState::taskInProgress() const
{
	return task != NO_TASK;
}