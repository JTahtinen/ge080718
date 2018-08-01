#include "surfacepool.h"
#include "log.h"

GraphicsPool::GraphicsPool()
{
	_components.reserve(50);
}

GraphicsPool::~GraphicsPool()
{
	for (unsigned int i = 0; i < _components.size(); ++i)
	{
		delete _components[i];
		_components[i] = nullptr;
	}
}

int GraphicsPool::addComponent(GraphicsComponent* component)
{
	if (component)
	{
		for (unsigned int i = 0; i < _components.size(); ++i)
		{
			if (_components[i] == component)
			{
				Log::instance().logAndPrintMessage("Surface addition ignored: Surface already in Surface Pool!");
				return (int)i;
			}
		}
		_components.push_back(component);
		return (int)_components.size() - 1;
	} 
	return -1;
}

GraphicsComponent* GraphicsPool::getComponent(int index)
{
	if (index < 0 || index >= (int)_components.size())
	{
		Log::instance().logAndPrintError("Could not load Surface from Pool: Invalid index!");
		return nullptr;
	}
	return _components[index];
}