#include "AssetManager.h"
#include "ecs/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::CreateProjectile(Vector2D position, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 32, 32, 1);
	projectile.AddComponent<SpriteComponent>(id, false);
	projectile.AddComponent<ProjectileComponent>(range, speed, vel);
	projectile.AddComponent<ColliderComponent>("projectile");
	projectile.AddGroup(Game::GroupProjectile);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
