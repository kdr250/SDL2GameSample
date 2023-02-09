#pragma once

#include "EntityComponentSystem.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rang, int sp, Vector2D vel) : range(rang), speed(sp), velocity(vel) {};

	~ProjectileComponent() {};

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void Update() override
	{
		distance += speed;

		if (distance > range) {
			SDL_Log("Out of Range!");
			entity->Destroy();
		}
		else if (
			transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y
		) {
			entity->Destroy();
		}
	}

private:
	TransformComponent* transform;

	int range;
	int speed;
	int distance;
	Vector2D velocity;
};
