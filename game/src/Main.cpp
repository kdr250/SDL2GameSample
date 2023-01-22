#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Game.h"

int main(int argc, char* args[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = nullptr;

	game = new Game();

	game->Init("SDL Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->IsRunning()) {
		frameStart = SDL_GetTicks();

		game->HandleEvnets();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}
