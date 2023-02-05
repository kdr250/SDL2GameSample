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

bool Game::isRunning = false;

auto& player(manager.AddEntity());

const char* mapFile = "asset/terrain_ss.png";

enum GroupLabel : std::size_t
{
	GroupMap,
	GroupPlayer,
	GroupEnemies,
	GroupCollider
};

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
	Map::LoadMap("asset/map.map", 25, 20);

	// ECS Implementation
	player.AddComponent<TransformComponent>(4);
	player.AddComponent<SpriteComponent>("asset/player_anims.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(GroupPlayer);
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

auto& tiles(manager.GetGroup(GroupMap));
auto& players(manager.GetGroup(GroupPlayer));
auto& enemies(manager.GetGroup(GroupEnemies));

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	Vector2D playerVelocity = player.GetComponent<TransformComponent>().velocity;
	int playerSpeed = player.GetComponent<TransformComponent>().speed;

	for (auto tile : tiles) {
		tile->GetComponent<TileComponent>().destinationRect.x += -(playerVelocity.x * playerSpeed);
		tile->GetComponent<TileComponent>().destinationRect.y += -(playerVelocity.y * playerSpeed);
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	for (auto& tile : tiles) {
		tile->Draw();
	}
	for (auto& player : players) {
		player->Draw();
	}
	for (auto& enemy : enemies) {
		enemy->Draw();
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

void Game::AddTile(int sourceX, int sourceY, int xpos, int ypos)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(sourceX, sourceY, xpos, ypos, mapFile);
	tile.AddGroup(GroupMap);
}
