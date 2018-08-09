#include "gameview.h"
#include "graphics.h"
#include "renderer.h"
#include "globals.h"
#include "game.h"

GameView::GameView(float xStart, float yStart, float xEnd, float yEnd, int width, int height, const Game* game)
	: UIComponent(xStart, yStart, xEnd, yEnd, width, height)
	, _game(game)
{
	
	_tasks.reserve(10);
	_tasks.push_back(RENDER);
	globals::renderer->setAmbientLight(0.3f);
}

GameView::~GameView()
{
}

void GameView::update(GraphicsComponent* target)
{
	_tasks.push_back(RENDER);
	for (unsigned int i = 0; i < _tasks.size(); ++i)
	{
		Task task = _tasks.back();
		_tasks.pop_back();
		switch (task)
		{
		case RENDER:
			Renderer* renderer = globals::renderer;
			const GameData& data = _game->getGameData();
			const std::vector<Light*>& lights = data.lights;
			const std::vector<Actor*>& actors = data.actors;
			const Map* map = data.map;
			const Camera* camera = data.camera;
			for (const Light* light : lights)
			{
				renderer->addRenderableLight(light);
			}
			map->render(_graphicsComponent, camera);

			for (const Actor* actor : actors)
			{
				actor->render(_graphicsComponent, camera);
			}
			renderer->clearRenderableLights();
			break;
		}
	}
	UIComponent::update(target);
}

void GameView::onNotify(const Entity* entity, const Message message)
{
	switch (message)
	{
	case ENTITY_MOVED:
	case ENTITY_ADDED:
	case LIGHT_ACTIVATED:
		_tasks.push_back(RENDER);
		break;
	}
}