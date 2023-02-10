#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "EntityComponentSystem.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) :
		labelText(text), labelFont(font), textColor(color)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	};

	~UILabel() {};

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	};

	void Draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	};

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
};
