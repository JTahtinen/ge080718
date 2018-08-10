#pragma once
#include "state.h"
#include "gameview.h"
#include "player.h"
#include "actor.h"
#include "npc.h"
#include "subject.h"
#include <vector>

class Game : public State
{
	Subject					_subject;
	GameView*				_gameView;
	GameData				_gameData;
public:
	static float			frameTime;
public:
	Game(const Window* win);
	~Game();
	void handleInput();
	void addLight(Light* light);
	void addNPC(NPC* npc);
	virtual void update(Window* win, float frameTime) override;
	const GameData& getGameData() const;
private:
	void updateEntities();
	void updateEntities(std::vector<Entity*>& entities);
};