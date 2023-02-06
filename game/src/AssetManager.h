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

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};