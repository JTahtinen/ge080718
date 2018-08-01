#include "frame.h"

Frame::Frame(float xStart, float yStart, float xEnd, float yEnd, const UIComponent* comp)
	: _xStart(xStart)
	, _yStart(yStart)
	, _xEnd(xEnd)
	, _yEnd(yEnd)
	, _comp(comp)
{

}

Frame::Frame(float xStart, float yStart, float xEnd, float yEnd)
	: Frame(xStart, yStart, xEnd, yEnd, nullptr)
{

}

void Frame::setComponent(const UIComponent *comp)
{
	_comp = comp;
}

void Frame::update(Surface* target)
{
	if (_comp)
	{

		int targetHalfWidth = target->getWidth() / 2;
		int targetHalfHeight = target->getHeight() / 2;

		int targetXStart = (int)(_xStart * targetHalfWidth + targetHalfWidth);
		int targetYStart = (int)(_yStart * targetHalfHeight + targetHalfHeight);
		int targetXEnd = (int)(_xEnd * targetHalfWidth + targetHalfWidth);
		int targetYEnd = (int)(_yEnd * targetHalfHeight + targetHalfHeight);

		target->blit(targetXStart, targetYStart, targetXEnd, targetYEnd, *(_comp->getSurface()));
	}

}