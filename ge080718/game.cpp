#include "game.h"
#include "testdata.h"
#include "input.h"
#include "globals.h"
#include "ai.h"

Game::Game(const Window* win)
	: State(win)
{
	Light::loadAssets();
	GraphicsPool* surfaces = TestData::instance().surfaces;
	Player* player = new Player(250, 200, TestData::instance().dudeMat);
	_gameData.setPlayer(player);
	//_gameData.setMap(Map::createDefaultMap());
	_gameData.setMap(Map::loadMap("map.png"));
	_gameData.setCamera(new Camera(player, 400, 300, _gameData.map));
	_gameView = new GameView(-0.8f, -0.8f, 0.8f, 0.8f, 400, 300, this);
	for (unsigned int i = 0; i < 10; ++i)
	{
		addNPC(new NPC(40.0f + i * 40.0f, 40.0f + i * 40.0f, TestData::instance().dudeMat));
	}
	_subject.addObserver(_gameView);
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
		Vec2 pos = _gameData.player->getPos();
		pos.add(16, 16);
		addLight(new Light(pos));
	}
	if (input.poll(SDLK_s, KEY_TYPED))
	{
		const Vec2& pos = _gameData.player->getPos();
		NPC* npc = new NPC(pos + Vec2(34, 34)); 
		npc->setAI(&AI::defaultAI(this));
		npc->addHostile(_gameData.player);
		addNPC(npc);
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

void Game::addNPC(NPC* npc)
{
	_gameData.addNPC(npc);
	addEntity(npc);
	_subject.notify(npc, ENTITY_ADDED);
	Log::msg("NPC added!");
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
	updateEntities(_gameData.entities);
}

void Game::updateEntities(std::vector<Entity*>& entities)
{
	for (Entity* entity : entities)
	{
		entity->update(this);
	}
}