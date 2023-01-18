#include "Game.h"

Game::Game()
{
}

Game::~Game() {
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Log("Subsystems Initialized!");

		window = SDL_CreateWindow(title, xPos, yPos, width, height, fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_MAXIMIZED);
		if (window) SDL_Log("Window Created!");

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) SDL_Log("Renderer Created!");

		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Game::HandleEvnets()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::Clean()
{
}

bool Game::IsRunning()
{
	return false;
}
