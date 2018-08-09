#include "camera.h"
#include "worldobject.h"
#include "map.h"

Camera::Camera(const WorldObject* target, int targetWidth, int targetHeight, const Map* map)
	: Entity(target->getPos())
	, _target(target)
	, _targetWidth(targetWidth)
	, _targetHeight(targetHeight)
{
	int halfViewWidth = targetWidth / 2;
	int halfViewHeight = targetHeight / 2;
	int mapWidth = map->getAbsWidth();
	int mapHeight = map->getAbsHeight();
	_bounds = Rect(
		(float)halfViewWidth, 
		(float)halfViewHeight,
		(float)(mapWidth - halfViewWidth), 
		(float)(mapHeight - halfViewHeight));
}

Camera::Camera(int targetWidth, int targetHeight, const Map* map)
	: Camera(nullptr, targetWidth, targetHeight, map)
{
}

void Camera::setTarget(const WorldObject* target)
{
	_target = target;
}

void Camera::update(Game* game)
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
	return Vec2(_targetWidth / 2.0f - _pos.x, _targetHeight / 2.0f - _pos.y);
}

Vec2 Camera::translate(const Vec2& pos) const
{
	return pos + getCameraCorrection();
}