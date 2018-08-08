#include "actor.h"
#include "testdata.h"
#include "game.h"
#include "globals.h"

Actor::Actor(float x, float y, const Material* sprite)
	: _target(nullptr)
	, _speed(5.0f)
	, WorldObject(x, y, sprite)
{
	_tasks.reserve(10);
}

Actor::Actor(const Vec2& pos)
	: Actor(pos.x, pos.y, TestData::instance().dudeMat)
{
}

Actor::Actor()
	: Actor(0, 0, TestData::instance().dudeMat)
{
}

void Actor::update(Game* game)
{
	updateWorldData(game);
	if (this->isMoving())
	{
		pushTask(SEEK_TARGET);
	}
	handleTasks();
	_vel.normalize().mul(_speed);
	WorldObject::update(game);
}

void Actor::move(const Vec2& dir, float speed)
{
	_vel = dir.getNormal() * speed;
}



void Actor::selectClosestTarget()
{

	static Usable* potentialTarget = nullptr;
	static unsigned int entityIndex = 0;
	std::vector<FixedEntity*>& entities = _worldData.potentialTargets;


	if (entities.size() > 0)
	{
		unsigned int i = 0;
		float distance = math::distance(_pos, entities[i]->getPos());
		for (unsigned int j = 1; j < entities.size(); ++j)
		{
			float newDistance = math::distance(_pos, entities[j]->getPos());
			if (newDistance < distance)
			{
				distance = newDistance;
				i = j;
			}
		}
		entityIndex = i;
		potentialTarget = entities[entityIndex];
	}


	if (potentialTarget != _target)
	{
		if (_target)
		{
			_target->target(false);
		}
		_target = potentialTarget;
		if (_target)
		{
			_target->target(true);
		}
	}

	if (entities.empty()) potentialTarget = nullptr;

}

void Actor::pushTask(ActorTask task)
{
	_tasks.push_back(task);
}

void Actor::handleTasks()
{
	for (unsigned int i = 0; i < _tasks.size(); ++i)
	{
		switch (_tasks[i])
		{
		case MOVE_UP:
			_vel.add(0, -1.0f);
			break;
		case MOVE_DOWN:
			_vel.add(0, 1.0f);
			break;
		case MOVE_LEFT:
			_vel.add(-1.0f, 0);
			break;
		case MOVE_RIGHT:
			_vel.add(1.0f, 0);
			break;
		case SEEK_TARGET:
			selectClosestTarget();
			break;
		case SWITCH_TARGET:
			selectNextTarget();
			break;
		case ACTIVATE_TARGET:
			if (_target)
			{
				_target->use(this);
			}
			break;
		default:
			break;
		}
	}
	_tasks.clear();
}

void Actor::selectNextTarget()
{

	Usable* newTarget = nullptr;
	std::vector<FixedEntity*>& entities = _worldData.potentialTargets;

	if (!entities.empty() && !_target)
	{
		newTarget = entities[0];
	}
	else
	{
		unsigned int size = entities.size();
		for (unsigned int i = 0; i < size; ++i)
		{
			if (entities[i] == _target)
			{
				if (i < size - 1)
				{
					newTarget = entities[i + 1];
				}
				else
				{
					newTarget = entities[0];
				}
			}
		}
	}
	targetEntity(newTarget);
}

void Actor::targetEntity(Usable* entity)
{
	if (_target)
	{
		_target->target(false);
	} 
	_target = entity;
	if (_target)
	{
		_target->target(true);
	}
}

void Actor::updateWorldData(Game* game)
{
	_worldData.potentialTargets.clear();
	_worldData.nearbyEntities.clear();
	if (game)
	{
		const GameData& gameData = game->getGameData();
		_worldData.potentialTargets = gameData.map->getEntitiesFromArea(_pos, 4);
	}
	else
	{
		Log::err("Could not fill ActorWorldData: Null parameters!");
	}
}