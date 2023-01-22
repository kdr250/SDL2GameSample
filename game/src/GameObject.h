#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xPosition;
	int yPosition;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;

};

