#include "input.h"

unsigned int Input::MAX_KEYS = 255;

Input::Input()
{
	_keys.reserve(MAX_KEYS);
	_keysPressed.reserve(MAX_KEYS);
	_keysTyped.reserve(MAX_KEYS);
	_keysReleased.reserve(MAX_KEYS);

	addKey(SDLK_UP);
	addKey(SDLK_DOWN);
	addKey(SDLK_LEFT);
	addKey(SDLK_RIGHT);
	addKey(SDLK_ESCAPE);
	addKey(SDLK_a);
	addKey(SDLK_b);
	addKey(SDLK_c);
	addKey(SDLK_d);
	addKey(SDLK_e);
	addKey(SDLK_f);
	addKey(SDLK_g);
	addKey(SDLK_h);
	addKey(SDLK_i);
	addKey(SDLK_j);
	addKey(SDLK_k);
	addKey(SDLK_l);
	addKey(SDLK_m);
	addKey(SDLK_n);
	addKey(SDLK_o);
	addKey(SDLK_p);
	addKey(SDLK_q);
	addKey(SDLK_r);
	addKey(SDLK_s);
	addKey(SDLK_t);
	addKey(SDLK_u);
	addKey(SDLK_v);
	addKey(SDLK_w);
	addKey(SDLK_x);
	addKey(SDLK_y);
	addKey(SDLK_z);
	addKey(SDLK_TAB);
}

void Input::update()
{
	for (unsigned int i = 0; i < _keys.size(); ++i)
	{
		_keysReleased[i] = false;
		_keysTyped[i] = false;
	}

	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
		{
			SDL_Keycode key = ev.key.keysym.sym;
			for (unsigned int i = 0; i < _keys.size(); ++i)
			{
				if (_keys[i] == key)
				{
					_keysPressed[i] = true;
					_keysTyped[i] = true;
					break;
				}
			}
		}
		else if (ev.type == SDL_KEYUP)
		{
			SDL_Keycode key = ev.key.keysym.sym;
			for (unsigned int i = 0; i < _keys.size(); ++i)
			{
				if (_keys[i] == key)
				{
					_keysReleased[i] = true;
					_keysPressed[i] = false;
					break;
				}
			}
		}
	}
}

bool Input::poll(SDL_Keycode key, KeyState state) const
{
	bool keyFound = false;
	unsigned int keyNum;

	for (unsigned int i = 0; i < _keys.size(); ++i)
	{
		if (_keys[i] == key)
		{
			keyNum = i;
			keyFound = true;
			break;
		}
	}
	if (!keyFound)
	{
		Log::warning("Key not found");
		return false;
	}

	switch (state)
	{
	case KEY_PRESSED:
		return _keysPressed[keyNum];
	case KEY_TYPED:
		return _keysTyped[keyNum];
	case KEY_RELEASED:
		return _keysReleased[keyNum];
	}
	return false;
}

bool Input::poll(SDL_Keycode key) const
{
	return poll(key, KEY_PRESSED);
}

void Input::addKey(SDL_Keycode key)
{
	for (unsigned int i = 0; i < _keys.size(); ++i)
	{
		if (_keys[i] == key)
		{
			Log::warning("Key already added!");
			return;
		}
	}
	_keys.push_back(key);
	_keysPressed.push_back(false);
	_keysTyped.push_back(false);
	_keysReleased.push_back(false);
}

Input& Input::instance()
{
	static Input input;
	return input;
}