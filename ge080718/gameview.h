#pragma once
#include "uicomponent.h"
#include "map.h"
#include "gamedata.h"
#include "entity.h"
#include "camera.h"
#include "light.h"
#include "surface.h"
#include <vector>
#include "observer.h"
#include "task.h"

class GameView : public UIComponent, public Observer
{
	std::vector<Task>				_tasks;
	const Game*						_game;
public:
	GameView(float xStart, float yStart, float xEnd, float yEnd, int width, int height, const Game* game);
	~GameView();
	void update(GraphicsComponent* target) override;
	virtual void onNotify(const Entity* entity, const Message message) override;
};