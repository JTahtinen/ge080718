#pragma once
#include "fixedentity.h"

class Door : public FixedEntity
{
public:
	Door(float x, float y, const Material* material, bool open);
	Door(float x, float y, const Material* material);
	virtual void use(Actor* actor) override;
	bool isOpen() const;
};