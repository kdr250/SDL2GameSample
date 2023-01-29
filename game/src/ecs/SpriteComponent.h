#pragma once

#include <SDL2/SDL.h>

#include "Components.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	};

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		sourceRect.x = sourceRect.y = 0;
		sourceRect.w = transform->width;
		sourceRect.h = transform->height;
	};

	void Update() override
	{
		destinationRect.x = (int)transform->position.x;
		destinationRect.y = (int)transform->position.y;
		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;
	};

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	};
};
