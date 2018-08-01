#pragma once
#include "window.h"
#include "glew.h"

class GLWindow : public Window
{
	SDL_GLContext			_glContext;
public:
	GLWindow(int width, int height, const std::string& title);
	void clear();
	virtual void update(const GraphicsComponent* graphics);
};