#pragma once
#include "graphicscomponent.h"

struct Material
{
	GraphicsComponent*		texture;
	float					friction;
	float					specular;
	
	Material(GraphicsComponent* texture, float friction, float specular);
};