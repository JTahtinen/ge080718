#pragma once
#include "fixedentity.h"

class Door : public FixedEntity
{
public:
	Door(const Material* material, bool open);
	Door(const Material* material);
	virtual void use() override;
	virtual void target() override;
	bool isOpen() const;
};