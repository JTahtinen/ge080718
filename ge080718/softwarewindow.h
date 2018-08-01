#pragma once
#include "window.h"

class SoftwareWindow : public Window
{
public:
	SoftwareWindow(int widht, int height, const std::string& title);
	virtual void update(const GraphicsComponent* graphics);
};