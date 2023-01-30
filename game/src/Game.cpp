#include <string>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Vector2D.h"
#include "ecs/Components.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

auto& tile0(manager.AddEntity());
auto& tile1(manager.AddEntity());
auto& tile2(manager.AddEntity());

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
	tile0.AddComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.AddComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.AddComponent<ColliderComponent>("dirt");
	tile2.AddComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.AddComponent<ColliderComponent>("grass");

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("asset/player.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");

	wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("asset/dirt.png");
	wall.AddComponent<ColliderComponent>("wall");
}

void Game::HandleEvnets()
{
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

	for (auto collider : colliders) {
		Collision::AABB(player.GetComponent<ColliderComponent>(), *collider);
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	// map->DrawMap();
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
