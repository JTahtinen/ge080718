#pragma once
#include "entity.h"
#include "rect.h"
#include "graphicsComponent.h"

class Map;
class WorldObject;

class Camera : public Entity
{
	const WorldObject*			_target;
	const GraphicsComponent*	_view;
	Rect						_bounds;
	int							_targetWidth;
	int							_targetHeight;
public:
	Camera(const WorldObject* target, int targetWidth, int targetHeight, const Map* map);
	Camera(int targetWidth, int targetHeight, const Map* map);
	void setTarget(const WorldObject* target);
	virtual void update(Game* game) override;
	Vec2 getCameraCorrection() const;
	Vec2 translate(const Vec2& pos) const;
};