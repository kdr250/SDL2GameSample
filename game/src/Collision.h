#pragma once

#include <SDL2/SDL.h>
#include "ecs/Components.h"

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);
};

