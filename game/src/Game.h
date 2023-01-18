#pragma once
#include <SDL2/SDL.h>

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
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};
