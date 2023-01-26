#pragma once

#include "Components.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	};

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		position = &entity->GetComponent<PositionComponent>();

		sourceRect.x = sourceRect.y = 0;
		sourceRect.w = sourceRect.h = 32;
		destinationRect.w = destinationRect.h = 64;
	};

	void Update() override
	{
		destinationRect.x = position->x();
		destinationRect.y = position->y();
	};

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	};
};