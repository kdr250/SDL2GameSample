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

	bool isAnimated = false;
	int frame = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	};

	SpriteComponent(const char* path, int mFrame, int mSpeed)
	{
		isAnimated = true;
		frame = mFrame;
		speed = mSpeed;
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
		sourceRect.w = transform->width / 2;
		sourceRect.h = transform->height;
	};

	void Update() override
	{
		if (isAnimated) {
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
		}
		destinationRect.x = static_cast<int>(transform->position.x);
		destinationRect.y = static_cast<int>(transform->position.y);
		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;
	};

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	};
};
