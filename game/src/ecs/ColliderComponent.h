#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void Init() override
	{
		if (!entity->HasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		texture = TextureManager::LoadTexture("asset/coltex.png");
		
		sourceRect = { 0, 0, 32, 32 };
		destinationRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void Update() override
	{
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destinationRect.x = collider.x - Game::camera.x;
		destinationRect.y = collider.y - Game::camera.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
	}
};
