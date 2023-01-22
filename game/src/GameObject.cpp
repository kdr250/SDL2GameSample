#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;
	objectTexture = TextureManager::LoadTexture(textureSheet, renderer);

	xPosition = x;
	yPosition = y;
}

void GameObject::Update()
{
	xPosition++;
	yPosition++;

	sourceRect.h = 32;
	sourceRect.w = 32;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = xPosition;
	destinationRect.y = yPosition;
	destinationRect.w = sourceRect.w * 2;
	destinationRect.h = sourceRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}
