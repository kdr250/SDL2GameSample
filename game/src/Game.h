#pragma once
#include <SDL2/SDL.h>
#ifdef _WINDOWS
    #include <SDL2/SDL_image.h>
#else
    #include <SDL2_image/SDL_image.h>
#endif

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

	static SDL_Renderer* renderer;

private:
	int counter;
	bool isRunning;
	SDL_Window* window;
	SDL_Texture* playerTexture;
	SDL_Rect source, destination;

};
