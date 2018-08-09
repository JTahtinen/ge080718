#include "worldobject.h"
#include "physics.h"
#include "globals.h"
#include "game.h"
#include "renderer.h"
#include "subject.h"
#include "rect.h"
#include "map.h"

WorldObject::WorldObject(float x, float y, const Material* sprite)
	: Entity(x, y)
	, _sprite(sprite)
{
}

WorldObject::WorldObject(const Vec2& pos, const Material* sprite)
	: WorldObject(pos.x, pos.y, sprite)
{
}

WorldObject::WorldObject(const Material* sprite)
	: WorldObject(0, 0, sprite)
{
}


void WorldObject::update(Game* game)
{
	const GameData& gameData = game->getGameData();
	const Map* map = gameData.map;
	setWalkMaterial(map->getTileAtAbsPos(_pos.x + 16, _pos.y + 16)->getMaterial());
	
	if (_walkMaterial)
	{
		_vel = Physics::instance().calcFriction(_walkMaterial->friction, _vel);
	}
	collisionCheck(map);
	std::vector<Actor*> actors = gameData.actors;
	for (unsigned int i = 0; i < actors.size(); ++i)
	{
		Actor* actor = actors[i];
		if (actor == this) continue;
		
		if (collisionCheck(*actor))
		{
			//Log::msg("Collision!");
		}
	}
	_pos += _vel;
	if (_vel.length() != 0.0f)
	{
		subject->notify(this, ENTITY_MOVED);
	}
	Entity::update(game);
}

void WorldObject::render(GraphicsComponent* target, const Camera* camera) const
{
	if (_sprite)
	{
		Rect dimensions = { _pos.x, _pos.y, _pos.x + 32, _pos.y + 32};
		const Vec2& camCorr = camera->getCameraCorrection();
		globals::renderer->renderMaterial(_sprite, dimensions, (int)camCorr.x, (int)camCorr.y, target);
		//target->blit((int)(_pos.x - 16 + camCorr.x), (int)(_pos.y - 16 + camCorr.y),
		//	(int)(_pos.x + 16 + camCorr.x), (int)(_pos.y + 16 + camCorr.y), *_sprite);
	}
}

const Vec2& WorldObject::getPos() const
{
	return _pos;
}

bool WorldObject::collisionCheck(const Rect& collider)
{
	Rect myCollider =
		Rect(_pos.x - 15.0f, _pos.y - 15.0f,
			_pos.x + 15.0f, _pos.y + 15.0f);
	
	Collision collision = Physics::instance().collision(myCollider, _vel, collider);

	if (collision.xCollision)
	{
		//if (!collision.yCollision)
	//	{
			if (_vel.x > 0)
			{
				_vel.setX(collider.x1 - myCollider.x2 - 1);
			}
			else if (_vel.x < 0) {
				_vel.setX(collider.x2 - myCollider.x1 + 1);
			}
	//	}
	}
	if (collision.yCollision)
	{
		if (_vel.y > 0)
		{
			_vel.setY(collider.y1 - myCollider.y2 - 1);
		}
		else if (_vel.y < 0) {
			_vel.setY(collider.y2 - myCollider.y1 + 1);
		}
	}

	return (collision.xCollision || collision.yCollision);

}

bool WorldObject::collisionCheck(const Entity& other)
{
	const Vec2& otherPos = other.getPos();
	
	Rect otherCollider =
		Rect(otherPos.x - 16.0f, otherPos.y - 16.0f, 
			otherPos.x + 16.0f, otherPos.y + 16.0f);
		
	return (collisionCheck(otherCollider));
}

bool WorldObject::collisionCheck(const Map* map)
{
	if (!this->isMoving()) return false;
	bool collided = false;
	Vec2 nextPos = _pos + _vel;
	const std::vector<Rect> colliders = map->getSurroundingColliders(_pos.x, _pos.y);
	for (unsigned int i = 0; i < colliders.size(); ++i)
	{
		if (collisionCheck(colliders[i]))
		{
			collided = true;
		}
	}
	return collided;
}

void WorldObject::setWalkMaterial(const Material* material)
{
	_walkMaterial = material;
}