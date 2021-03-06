#pragma once
#include "entity.h"
#include "material.h"
#include "camera.h"
#include "light.h"
#include "physics.h"
#include <vector>

class Game;

class WorldObject : public Entity
{
protected:
	const Material*		_sprite;
	const Material*		_walkMaterial;
public:
	WorldObject(float x, float y, const Material* sprite);
	WorldObject(const Vec2& pos, const Material* sprite);
	WorldObject(const Material *sprite);
	virtual void update(Game* game) override;
	virtual void render(GraphicsComponent* target, const Camera* camera) const;
	const Vec2& getPos() const;
	bool collisionCheck(const Collider& collider);
	bool collisionCheck(const Entity& other);
	bool collisionCheck(const Map* map);
private:
	void setWalkMaterial(const Material* material);
};