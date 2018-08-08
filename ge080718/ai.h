#pragma once
#include <vector>

class Game;
class NPC;
class Entity;

enum AI_Stance
{
	NEUTRAL, FRIENDLY, HOSTILE
};

class AI
{
	const Game*					_game;
public:
	void update(NPC* npc) const;
private:
	AI(const Game* game);
	void act(NPC* actor) const;
	void attack(NPC* actor, const Entity* target) const;
public:
	inline static AI& defaultAI(const Game* game)
	{
		static AI default_AI(game);
		return default_AI;
	}
};