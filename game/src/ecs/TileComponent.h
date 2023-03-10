#pragma once

#include <SDL2/SDL.h>

#include "EntityComponentSystem.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;
	Vector2D position;

	TileComponent() = default;

	TileComponent(int sourceX, int sourceY, int xpos, int ypos, int tileSize, int tileScale, std::string id)
	{
		texture = Game::assetManager->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
		sourceRect.w = sourceRect.h = tileSize;

		destinationRect.x = xpos;
		destinationRect.y = ypos;
		destinationRect.w = destinationRect.h = tileSize * tileScale;
	}

	~TileComponent()
	{
	}

	void Update() override
	{
		destinationRect.x = position.x - Game::camera.x;
		destinationRect.y = position.y - Game::camera.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
	}
};
