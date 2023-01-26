#include <string>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "EntityComponentSystem.h"
#include "Components.h"

GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.AddEntity());

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

	player = new GameObject("asset/player.png", 0, 0);
	enemy = new GameObject("asset/enemy.png", 50, 50);
	map = new Map();

	newPlayer.AddComponent<PositionComponent>();
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
	player->Update();
	enemy->Update();
	manager.Update();

	std::cout << newPlayer.GetComponent<PositionComponent>().x() << "," <<
		newPlayer.GetComponent<PositionComponent>().y() << std::endl;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	enemy->Render();
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
