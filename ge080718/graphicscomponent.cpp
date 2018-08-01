#include "graphicscomponent.h"
#include "swgraphicscomponent.h"
#include "globals.h"

GraphicsComponent::GraphicsComponent()
{
}

GraphicsComponent* GraphicsComponent::loadGraphicsComponent(const std::string& filepath)
{
	if (globals::renderType == SOFTWARE)
	{
		return SWGraphicsComponent::loadGraphicsComponent(filepath);
	}
	return nullptr;
}