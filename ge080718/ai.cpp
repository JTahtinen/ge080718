#include "ai.h"
#include "math.h"
#include "entity.h"
#include "npc.h"
#include "game.h"

AI::AI(const Game* game)
	: _game(game)
{
}

void AI::update(NPC* npc) const
{
	NPCState& state = npc->_state;
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
				const Vec2& pos = npc->getPos();
				float dist;
				for (const Actor* hostile : hostiles)
				{
					float nextDist = math::distance(pos, hostile->getPos());
					if (nextDist > 40.0f)
					{
						if (!suitableHostiles)
						{
							state.setTarget(hostile);
							suitableHostiles = true;
						}
						else 
						{
							if (nextDist < dist)
							{
								state.setTarget(hostile);
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
		act(npc);
	}
}

void AI::act(NPC* npc) const
{
	switch(npc->_state.task)
	{
	case ATTACK:
		attack(npc, npc->_state.target);
		break;
	default:
		break;
	}
}

void AI::attack(NPC* npc, const Entity* target) const
{
	const Vec2& pos = npc->getPos();
	const Vec2& targetPos = target->getPos();

	Vec2 dir = -(pos - targetPos);
	npc->move(dir, 2.0f);
	if (math::distance(pos, targetPos) < 100.0f)
	{
		npc->_state.setTask(NO_TASK);
	}
}