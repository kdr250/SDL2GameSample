#pragma once

#include <SDL2/SDL.h>

#include "EntityComponentSystem.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	std::string path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "asset/water.png";
			break;
		case 1:
			path = "asset/dirt.png";
			break;
		case 2:
			path = "asset/grass.png";
			break;
		default:
			break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path.c_str());
		sprite = &entity->GetComponent<SpriteComponent>();
	}
};
