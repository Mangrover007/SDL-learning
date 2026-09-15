#include "../include/LWindow.h"
#include <SDL2/SDL_image.h>

LWindow gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gBackground;
SDL_Rect gBackgroundRect;


bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("Failed to initialize SDL Video subsystem.\n%s\n", SDL_GetError());
	success = false;
    }
    
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
	printf("Failed to initialize SDL_Image library.\n");
	printf("%s\n", IMG_GetError());
	success = false;
    }

    return success;
}


bool loadMedia()
{
    bool success = true;

    SDL_Surface* surface = IMG_Load("/home/mango/personal/SDL-learning/SDL/SDL-window-events/assets/cute-pokemon.png");
    if (surface == nullptr)
    {
	printf("Error loading image!\n");
	printf("%s\n", IMG_GetError());
	success = false;
    }
    else
    {
	gBackground = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (gBackground == nullptr)
	{
	    printf("Error converting surface to texture!\n");
	    printf("%s\n", SDL_GetError());
	    success = false;
	}
	else
	{
	    gBackgroundRect.w = surface->w;
	    gBackgroundRect.h = surface->h;
	}
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
	    else
	    {
		gWindow.handleEvents(e);
	    }
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	int screen_width, screen_height;
	gWindow.getWindowSize(&screen_width, &screen_height);

	gBackgroundRect.x = (screen_width - gBackgroundRect.w) / 2;
	gBackgroundRect.y = (screen_height - gBackgroundRect.h) / 2;

	SDL_RenderCopy(gRenderer, gBackground, nullptr, &gBackgroundRect);

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

    gRenderer = gWindow.createRenderer();

    if (gRenderer == nullptr)
    {
	printf("Failed to create a renderer for the window!\n%s\n", SDL_GetError());
	return -1;
    }

    if (!loadMedia())
    {
	printf("Failed to load media!\n");
	return -1;
    }

    gameLoop();

    close();

    return 0;
}

