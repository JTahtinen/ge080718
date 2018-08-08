#pragma once
#include "actor.h"
#include "usable.h"

class Player : public Actor
{
public:
	Player(float x, float y, const Material* sprite);
	Player(const Vec2& pos, const Material* sprite);
	Player();
	virtual void update(Game* game) override;
private:
	void handleInput();
};