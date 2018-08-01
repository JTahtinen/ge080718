#pragma once
#include <SDL.h>
#include <vector>
#include "globals.h"

enum KeyState
{
	KEY_PRESSED, KEY_TYPED, KEY_RELEASED
};

class Input
{
	static unsigned int			MAX_KEYS;
	std::vector<SDL_Keycode>	_keys;
	std::vector<bool>			_keysPressed;
	std::vector<bool>			_keysTyped;
	std::vector<bool>			_keysReleased;
public:
	static Input& instance();
	void update();
	bool poll(SDL_Keycode key, KeyState state) const;
	bool poll(SDL_Keycode key) const;
	void addKey(SDL_Keycode key);
private:
	Input();
};