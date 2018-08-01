#pragma once
#include <vector>
#include "graphicscomponent.h"

class GraphicsPool
{
	std::vector<GraphicsComponent*> _components;
public:
	GraphicsPool();
	~GraphicsPool();
	int addComponent(GraphicsComponent* component);
	GraphicsComponent* getComponent(int index);
};