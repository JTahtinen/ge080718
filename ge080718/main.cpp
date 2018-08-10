#include <SDL.h>
#include <iostream>
#include "application.h"
#include "globals.h"
#include "timer.h"
#include "testdata.h"

int main(int argc, char** argv)
{
	{
		Log& log = Log::instance();

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
#ifdef _DEBUG
			log.logAndPrintError("SDL_Init Failed!");
#endif
		}
		else
		{
#ifdef _DEBUG
			log.logAndPrintMessage("SDL_Init successful!");
#endif
			Application* app = new Application(800, 600, "GE080718", SOFTWARE);
			app->run();
			delete app;
			app = nullptr;

		}
		SDL_Quit();
	}
	Log::msg("Press Enter to continue...");
	std::cin.get();
	return 0;
}