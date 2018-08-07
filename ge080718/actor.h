#pragma once
#include "worldobject.h"
#include "vec2.h"
#include "surface.h"
#include "ai.h"
#include "actorstate.h"

class Actor : public WorldObject
{
	friend class AI;

	ActorState		_state;
	AI*				_ai;
public:
	Actor(float x, float y, const Material* sprite);
	Actor(const Vec2& pos);
	Actor();
	virtual void update(Game* game) override;
	void move(const Vec2& dir, float speed);
	void setAI(AI* ai);
	void addHostile(const Actor* actor);
};