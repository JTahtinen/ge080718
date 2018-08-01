#include "camera.h"
#include "worldobject.h"
#include "map.h"

Camera::Camera(const WorldObject* target, const GraphicsComponent* view, const Map* map)
	: _target(target)
	, _view(view)
{
	int halfViewWidth = _view->getWidth() / 2;
	int halfViewHeight = _view->getHeight() / 2;
	int mapWidth = map->getAbsWidth();
	int mapHeight = map->getAbsHeight();
	_bounds = Rect(
		(float)halfViewWidth, 
		(float)halfViewHeight,
		(float)(mapWidth - halfViewWidth), 
		(float)(mapHeight - halfViewHeight));
}

Camera::Camera(const GraphicsComponent* view, const Map* map)
	: Camera(nullptr, view, map)
{
}

void Camera::setTarget(const WorldObject* target)
{
	_target = target;
}

void Camera::update()
{
	if (_target)
	{
		_pos = _target->getPos();
	}
	if (_pos.x < _bounds.x1) _pos.x = _bounds.x1;
	if (_pos.y < _bounds.y1) _pos.y = _bounds.y1;
	if (_pos.x > _bounds.x2) _pos.x = _bounds.x2;
	if (_pos.y > _bounds.y2) _pos.y = _bounds.y2;
}

Vec2 Camera::getCameraCorrection() const
{
	return Vec2(_view->getWidth() / 2.0f - _pos.x, _view->getHeight() / 2.0f - _pos.y);
}
