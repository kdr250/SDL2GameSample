#pragma once

#include <SDL2/SDL.h>

#include "EntityComponentSystem.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

	TileComponent() = default;

	TileComponent(int sourceX, int sourceY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
		sourceRect.w = sourceRect.h = 32;

		destinationRect.x = xpos;
		destinationRect.y = ypos;
		destinationRect.w = destinationRect.h = 64;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
	}
};
