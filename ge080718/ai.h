#pragma once
#include <vector>

class Game;
class Actor;
class Entity;

enum AI_Stance
{
	NEUTRAL, FRIENDLY, HOSTILE
};

class AI
{
	const Game*					_game;
public:
	void update(Actor* actor) const;
private:
	AI(const Game* game);
	void act(Actor* actor) const;
	void attack(Actor* actor, const Entity* target) const;
public:
	inline static AI& defaultAI(const Game* game)
	{
		static AI default_AI(game);
		return default_AI;
	}
};