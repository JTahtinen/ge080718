#pragma once
#include <string>
#include "window.h"
#include "game.h"
#include "renderer.h"
#include "testdata.h"
#include "menu.h"
#include <vector>

class Application
{
	Window*						_win;
	Game*						_game;
	Menu*						_menu;
	unsigned int				_currentState;
	std::vector<State*>			_states;
	bool						_running;
	
public:
	Application(int width, int height, const std::string& title, RendererType renderer);
	~Application();
	void run();
	void switchState(unsigned int state);
	void cycleState();
private:
	void handleInput();
};