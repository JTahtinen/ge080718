#include "gameview.h"
#include "graphics.h"
#include "renderer.h"
#include "globals.h"

GameView::GameView(float xStart, float yStart, float xEnd, float yEnd, int width, int height, const GameData& gameData)
	: UIComponent(xStart, yStart, xEnd, yEnd, width, height)
	, _actors(gameData.actors)
	, _lights(gameData.lights)
{
	_map = gameData.map;
	_camera = new Camera(_graphicsComponent, _map);
	_camera->setTarget(gameData.player);
	_tasks.reserve(10);
	_tasks.push_back(RENDER);
	globals::renderer->setAmbientLight(0.3f);
}

GameView::~GameView()
{
	delete _camera;
	_camera = nullptr;
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
			_camera->update();
			for (unsigned int i = 0; i < _lights.size(); ++i)
			{
				renderer->addRenderableLight(_lights[i]);
			}
			_map->render(_graphicsComponent, _camera);

			for (unsigned int i = 0; i < _actors.size(); ++i)
			{
				_actors[i]->render(_graphicsComponent, _camera);
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