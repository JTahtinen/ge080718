#pragma once
#include "entity.h"

enum Message
{
	ENTITY_MOVED, LIGHT_ACTIVATED, ENTITY_ADDED,
};

class Observer
{
public:
	virtual void onNotify(const Entity* entity, const Message message) {};
};