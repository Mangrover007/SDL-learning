#include "../include/LWindow.h"

LWindow::LWindow()
{
    mWindow = nullptr;
    this->init();
}

bool LWindow::init()
{
    SDL_Window* window = SDL_CreateWindow(
		"Hello window :D",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	    );

    if (window == nullptr)
    {
	printf("Could not create a window!\n%s\n", SDL_GetError());
	return false;
    }

    mWindow = window;
    return true;
}

SDL_Renderer* LWindow::createRenderer()
{
    SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
	printf("Could not create a renderer!\n%s\n", SDL_GetError());
	return nullptr;
    }

    return renderer;
}

void LWindow::free()
{
    SDL_DestroyWindow(mWindow);
}

