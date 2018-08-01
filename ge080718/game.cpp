#include "game.h"
#include "testdata.h"
#include "input.h"
#include "globals.h"

Game::Game(const Window* win)
	: State(win)
{
	Light::loadAssets();
	GraphicsPool* surfaces = TestData::instance().surfaces;
	Player* player = new Player(200.0f, 40.0f, TestData::instance().dudeMat);
	_gameData.setPlayer(player);
	//_gameData.setMap(Map::createDefaultMap());
	_gameData.setMap(Map::loadMap("map.png"));
	_gameView = new GameView(-0.8f, -0.8f, 0.8f, 0.8f, 400, 300, _gameData);
	for (unsigned int i = 0; i < 10; ++i)
	{
		addActor(new Actor(40.0f + i * 40.0f, 40.0f + i * 40.0f, TestData::instance().dudeMat));
	}
	_subject.addObserver(_gameView);
	std::vector<Actor*>& actors = _gameData.actors;
	actors[3]->setAI(&AI::defaultAI(this));
	actors[3]->addHostile(player);
	actors[3]->addHostile(actors[6]);
	addEntity(player);
}

Game::~Game()
{
	Light::deleteAssets();
	delete _gameView;
	_gameView = nullptr;
}

void Game::handleInput()
{
	Input& input = Input::instance();
	if (input.poll(SDLK_a, KEY_TYPED))
	{
		const Vec2& pos = _gameData.player->getPos();
		addLight(new Light(pos));
	}
	if (input.poll(SDLK_s, KEY_TYPED))
	{
		const Vec2& pos = _gameData.player->getPos();
		Actor* actor = new Actor(pos + Vec2(34, 34)); 
		actor->setAI(&AI::defaultAI(this));
		actor->addHostile(_gameData.player);
		addActor(actor);
	}
}

void Game::addEntity(Entity* entity)
{
	//entity->subject->addObserver(_gameView);
}

void Game::addLight(Light* light)
{
	_gameData.addLight(light);
	addEntity(light);
	_subject.notify(light, ENTITY_ADDED);
	Log::msg("Light added!");

}

void Game::addActor(Actor* actor)
{
	_gameData.addActor(actor);
	addEntity(actor);
	_subject.notify(actor, ENTITY_ADDED);
	Log::msg("Actor added!");
}

void Game::update(Window* win)
{
	handleInput();
	updateEntities();
	_gameView->update(_graphics);
	win->update(_graphics);
}

const GameData& Game::getGameData() const
{
	return _gameData;
}


void Game::updateEntities()
{
	std::vector<WorldObject*>& worldObjects = _gameData.worldObjects;
	std::vector<Actor*>& actors = _gameData.actors;
	std::vector<Light*>& lights = _gameData.lights;

	unsigned int i;
	for (i = 0; i < worldObjects.size(); ++i)
	{
		worldObjects[i]->update(this);
	}
	
	for (i = 0; i < actors.size(); ++i)
	{
		actors[i]->update(this);
	}

	for (i = 0; i < lights.size(); ++i)
	{
		lights[i]->update();
	}
}