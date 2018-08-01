#include "ai.h"
#include "math.h"
#include "entity.h"
#include "actor.h"
#include "game.h"

AI::AI(const Game* game)
	: _game(game)
{
}

void AI::update(Actor* actor) const
{
	ActorState& state = actor->_state;
	if (!state.taskInProgress())
	{
		switch (state.mood)
		{
		case IDLE:
			break;
		case ACTIVE:
			std::vector<const Actor*>& hostiles = state.hostiles;
			unsigned int numHostiles = hostiles.size();
			if (numHostiles > 0)
			{
				bool suitableHostiles = false;
				const Vec2& pos = actor->getPos();
				float dist;
				for (unsigned int i = 0; i < numHostiles; ++i)
				{
					float nextDist = distance(pos, hostiles[i]->getPos());
					if (nextDist > 40.0f)
					{
						if (!suitableHostiles)
						{
							state.setTarget(hostiles[i]);
							suitableHostiles = true;
						}
						else 
						{
							if (nextDist < dist)
							{
								state.setTarget(hostiles[i]);
							}
						}
						dist = nextDist;
					}
				}
				if (suitableHostiles)
				state.setTask(ATTACK);
			}
		}
	}
	else
	{
		act(actor);
	}
}

void AI::act(Actor* actor) const
{
	switch(actor->_state.task)
	{
	case ATTACK:
		attack(actor, actor->_state.target);
		break;
	default:
		break;
	}
}

void AI::attack(Actor* actor, const Entity* target) const
{
	const Vec2& pos = actor->getPos();
	const Vec2& targetPos = target->getPos();

	Vec2 dir = -(pos - targetPos);
	actor->move(dir, 2.0f);
	if (distance(pos, targetPos) < 100.0f)
	{
		actor->_state.setTask(NO_TASK);
	}
}