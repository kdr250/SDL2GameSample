#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Game.h"

int main(int argc, char* args[]) {
	Game* game = nullptr;

	game = new Game();

	game->Init("SDL Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->IsRunning()) {
		game->HandleEvnets();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}
