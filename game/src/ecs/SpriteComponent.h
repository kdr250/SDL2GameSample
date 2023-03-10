#pragma once

#include <SDL2/SDL.h>
#include <map>

#include "Components.h"
#include "../TextureManager.h"
#include "Animation.h"
#include "../AssetManager.h"

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
	int animationIndex = 0;
	std::map <const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		SetTexture(id);
	};

	SpriteComponent(std::string id, bool animated)
	{
		isAnimated = animated;

		Animation idle = Animation(0, 2, 200);
		Animation walk = Animation(1, 8, 200);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		SetTexture(id);
	};

	~SpriteComponent() {};

	void SetTexture(std::string id)
	{
		texture = Game::assetManager->GetTexture(id);
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
		if (isAnimated) {
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
		}

		sourceRect.y = animationIndex * transform->height;

		destinationRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destinationRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;
	};

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect, spriteFlip);
	};

	void Play(const char* animationName)
	{
		frame = animations[animationName].frame;
		animationIndex = animations[animationName].index;
		speed = animations[animationName].speed;
	}
};
