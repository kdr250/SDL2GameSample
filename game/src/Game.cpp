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

SDL_Rect Game::camera = { 0, 0, 800, 640 };

bool Game::isRunning = false;

AssetManager* Game::assetManager = new AssetManager(&manager);

auto& player(manager.AddEntity());

const char* mapFile = "asset/terrain_ss.png";

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

	assetManager->AddTexture("terrain", "asset/terrain_ss.png");
	assetManager->AddTexture("player", "asset/player_anims.png");

	map = new Map("terrain", 3, 32);
	map->LoadMap("asset/map.map", 25, 20);

	// ECS Implementation
	player.AddComponent<TransformComponent>(800.0f, 640.0f, 16, 16, 4);
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(GroupPlayer);
}

auto& tiles(manager.GetGroup(Game::GroupMap));
auto& players(manager.GetGroup(Game::GroupPlayer));
auto& colliders(manager.GetGroup(Game::GroupCollider));

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
	SDL_Rect playerCollider = player.GetComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.GetComponent<TransformComponent>().position;

	manager.Refresh();
	manager.Update();

	for (auto& collider : colliders) {
		SDL_Rect col = collider->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(col, playerCollider)) {
			player.GetComponent<TransformComponent>().position = playerPosition;
		}
	}

	camera.x = player.GetComponent<TransformComponent>().position.x - 400;
	camera.y = player.GetComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	for (auto& tile : tiles) {
		tile->Draw();
	}
	for (auto& collider : colliders) {
		collider->Draw();
	}
	for (auto& player : players) {
		player->Draw();
	}
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
