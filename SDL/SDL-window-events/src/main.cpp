#include "../include/LWindow.h"


LWindow gWindow;
SDL_Renderer* gRenderer;


bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("Failed to initialize SDL Video subsystem.\n%s\n", SDL_GetError());
	success = false;
    }

    gRenderer = gWindow.createRenderer();

    if (gRenderer == nullptr)
    {
	printf("Failed to create a renderer for the window!\n%s\n", SDL_GetError());
	success = false;
    }

    return success;
}


void gameLoop()
{
    SDL_Event e;
    bool quit = false;

    while (quit == false)
    {
	while (SDL_PollEvent(&e) != 0)
	{
	    if (e.type == SDL_QUIT)
	    {
		printf("Quit signal received??\n");
		quit = true;
	    }
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_RenderPresent(gRenderer);
    }
}


void close()
{
    SDL_DestroyRenderer(gRenderer);

    gWindow.free();

    SDL_Quit();
}


int main(int argc, char** argv)
{
    if (!init())
    {
	printf("Failed to initialize SDL!\n");
	return -1;
    }

    if (!gWindow.init())
    {
	printf("Failed to create a window!\n");
	return -1;
    }

    gameLoop();

    close();

    return 0;
}

