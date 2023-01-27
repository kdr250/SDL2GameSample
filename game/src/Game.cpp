#include <string>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Vector2D.h"
#include "ecs/Components.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.AddEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Log("Subsystems Initialized!");

		window = SDL_CreateWindow(title, xPos, yPos, width, height, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
		if (window) SDL_Log("Window Created!");

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_Log("Renderer Created!");
		}

		isRunning = true;
	}

	map = new Map();

	// ECS Implementation
	player.AddComponent<TransformComponent>(100, 100);
	player.AddComponent<SpriteComponent>("asset/player.png");
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
	manager.Refresh();
	manager.Update();
	player.GetComponent<TransformComponent>().position.Add(Vector2D(5.0f, 5.0f));

	if (player.GetComponent<TransformComponent>().position.x > 300)
	{
		player.GetComponent<SpriteComponent>().SetTexture("asset/enemy.png");
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.Draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	SDL_Log("Game Quit!");
}

bool Game::IsRunning()
{
	return isRunning;
}
