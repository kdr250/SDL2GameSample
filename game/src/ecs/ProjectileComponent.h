#pragma once

#include "EntityComponentSystem.h"
#include "Components.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rang, int sp) : range(rang), speed(sp)
	{

	};

	~ProjectileComponent() {};

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		distance += speed;

		if (distance > range) {
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
};
