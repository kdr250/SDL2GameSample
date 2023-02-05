#pragma once

#include <vector>
#include <SDL2/SDL.h>
#if defined _WIN32 || defined _WIN64
    #include <SDL2/SDL_image.h>
#else
    #include <SDL2_image/SDL_image.h>
#endif

class ColliderComponent;

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

	static void AddTile(int sourceX, int sourceY, int xpos, int ypos);
	static SDL_Renderer* renderer;
    static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;

private:
	int counter;
	SDL_Window* window;
};
