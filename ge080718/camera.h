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
public:
	Camera(const WorldObject* target, const GraphicsComponent* view, const Map* map);
	Camera(const GraphicsComponent* view, const Map* map);
	void setTarget(const WorldObject* target);
	virtual void update() override;
	Vec2 getCameraCorrection() const;
	Vec2 translate(const Vec2& pos) const;
};