#pragma once

#include <map>
#include <string>

#include "TextureManager.h"
#include "Vector2D.h"
#include "ecs/EntityComponentSystem.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	// Game Objects
	void CreateProjectile(Vector2D position, int range, int speed, std::string id);

	// Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};
