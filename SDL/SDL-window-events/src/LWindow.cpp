#include "../include/LWindow.h"

LWindow::LWindow()
{
    mWindow = nullptr;
    mFullscreen = false;
}



bool LWindow::init()
{
    mWindow = SDL_CreateWindow(
		"Hello window :D",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	    );

    if (mWindow == nullptr)
    {
	printf("Could not create a window!\n%s\n", SDL_GetError());
	return false;
    }

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




void LWindow::handleEvents(SDL_Event& e)
{
    /*
     * hyprland is eating up this event (SUPER + F) and resizing the window 
     * the event itself never gets to the program / window
     *
    if (e.key.keysym.sym == SDLK_f && (e.key.keysym.mod & KMOD_ALT))
    {
	printf("Full screen event\n");
	SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
    }
    */

    if (e.key.keysym.sym == SDLK_RETURN && (e.key.keysym.mod & KMOD_ALT))
    {
	if (mFullscreen == false)
	{
	    SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
	    mFullscreen = true;
	}
	else
	{
	    SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_MINIMIZED);
	    mFullscreen = false;
	}
    }
}


