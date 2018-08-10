#include "application.h"
#include "surface.h"
#include "input.h"
#include "log.h"
#include "softwarewindow.h"
#include "glwindow.h"
#include "globals.h"
#include "softwarerenderer.h"
#include "glrenderer.h"
#include "timer.h"

Application::Application(int width, int height, const std::string& title, RendererType renderer)
{
	_states.reserve(2);
	switch (renderer)
	{
	case SOFTWARE:
		_win = new SoftwareWindow(width, height, title);
		globals::renderer = new SoftwareRenderer();
		globals::renderType = SOFTWARE;
		break;
	case OPENGL:
		_win = new GLWindow(width, height, title);
		globals::renderer = new GLRenderer();
		globals::renderType = OPENGL;
		break;
	default:
		_win = new SoftwareWindow(width, height, title);
		globals::renderType = SOFTWARE;
		break;
	}
	_game = new Game(_win);
	_menu = new Menu(_win);
	_states.push_back(_menu);
	_states.push_back(_game);
	_currentState = 0;
}

Application::~Application()
{
	Log::msg("Closing application...");
	delete globals::renderer;
	delete _game;
	delete _win;
	delete _menu;
	globals::renderer = nullptr;
	_game = nullptr;
	_win = nullptr;
	_menu = nullptr;
}

void Application::run()
{
	_running = true;
	Timer fpsTimer;
	fpsTimer.start();
	Timer frame;
	frame.start();
	float frameTime = 0;
	unsigned int frames = 0;
	while (_running)
	{
		handleInput();
		_states[_currentState]->update(_win, frameTime);
		frameTime = frame.getElapsedTime();
		frame.reset();
		++frames;
		float elapsedTime = fpsTimer.getElapsedTime();
		if (elapsedTime >= 1.0f)
		{
			Log::msg("FPS: " + std::to_string(frames));
			fpsTimer.reset();
			frames = 0;

		}
	}
}

void Application::handleInput()
{
	Input& input = Input::instance();
	input.update();
	if (input.poll(SDLK_ESCAPE))
	{
		_running = false;
	}
	if (input.poll(SDLK_q, KEY_TYPED))
	{
		cycleState();
	}
}

void Application::switchState(unsigned int state)
{
	if (state < _states.size())
	_currentState = state;
}

void Application::cycleState()
{
	if (_currentState == _states.size() - 1) 
	{
		switchState(0);
	}
	else
	{
		switchState(_currentState + 1);
	}
}