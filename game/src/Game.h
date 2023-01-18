#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);
	void HandleEvnets();
	void Update();
	void Render();
	void Clean();

	bool IsRunning();

private:
	int counter;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* playerTexture;

};
