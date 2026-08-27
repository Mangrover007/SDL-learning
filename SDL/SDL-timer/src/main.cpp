#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <stdio.h>


#include "../include/LButton.h"
#include "../include/LTimer.h"


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font* gFont;


SDL_Color SDL_COL_BLACK = SDL_Color{0x00, 0x00, 0x00, 0xFF};
SDL_Color SDL_COL_WHITE = SDL_Color{0xFF, 0xFF, 0xFF, 0xFF};


LTexture infoText1; // press S to start/stop the timer
LTexture infoText2; // perss P to pause/resume the timer

LTexture gTimerTexture;

#include "../include/globals.h"


const char* fontPath = "/usr/share/fonts/OTF/ipam.ttf";
const char* WINDOW_NAME = "HELLO timer :D";


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("Error initializing SDL: %s\n", SDL_GetError());
	return false;
    }

    int IMG_INIT_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(IMG_INIT_FLAGS) != IMG_INIT_FLAGS)
    {
	printf("Error initializing SDL_image: %s\n", SDL_GetError());
	return false;
    }

    if (TTF_Init() != 0)
    {
	printf("Error initializing SDL_ttf: %s\n", SDL_GetError());
	return false;
    }

    gWindow = SDL_CreateWindow(
		WINDOW_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	    );

    if (gWindow == nullptr)
    {
	printf("Error creating SDL window: %s\n", SDL_GetError());
	return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == nullptr)
    {
	printf("Error creating Renderer for SDL Window: %s\n", SDL_GetError());
	return false;
    }

    gFont = TTF_OpenFont(fontPath, 28);

    if (gFont == nullptr)
    {
	printf("Failed to load font: %s\n", TTF_GetError());
	return false;
    }

    return true;
}


void close()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    TTF_CloseFont(gFont);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool loadMedia()
{
    bool success = true;

    infoText1 = LTexture();

    if (!infoText1.loadTTF("Press S to start/stop the timer", SDL_COL_BLACK))
    {
	printf("Failed to load text.\n");
	success = false;
    }

    if (!infoText2.loadTTF("Press P to pause/resume the timer", SDL_COL_BLACK))
    {
	printf("Failed to load text.\n");
	success = false;
    }

    return success;
}


void handleEvent(SDL_Event& e)
{
    // write custom events handlers here
    
}


#include <sstream>

void mainLoop()
{
    bool quit = false;
    SDL_Event e;

    LTimer timer = LTimer();
    std::stringstream timerText;

    while (quit == false)
    {
	while (SDL_PollEvent(&e) != 0)
	{
	    if (e.type == SDL_QUIT)
	    {
		quit = true;
	    }
	    else
	    {
		if (e.type == SDL_KEYDOWN)
		{
		    switch (e.key.keysym.sym)
		    {
			case SDLK_s:
			    if (!timer.isStarted())
			    {
				timer.start();
			    }
			    else
			    {
				timer.stop();
			    }
			    break;
			case SDLK_p:
			    if (!timer.isPaused())
			    {
				timer.pause();
			    }
			    else
			    {
				timer.unpause();
			    }
			    break;
		    }
		}
	    }
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// write code here
	infoText1.render((SCREEN_WIDTH - infoText1.getWidth()) / 2, 0);
	infoText2.render((SCREEN_WIDTH - infoText2.getWidth()) / 2, infoText1.getHeight() + 5);

	timerText.str("");
	timerText << timer.getTicks();

	gTimerTexture.loadTTF(timerText.str().c_str(), SDL_COL_BLACK);
	gTimerTexture.render((SCREEN_WIDTH - gTimerTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTimerTexture.getHeight()) / 2);

	SDL_RenderPresent(gRenderer);
    }

    printf("Exiting main loop...\n");
}


int main(int argc, char** argv)
{
    if (!init())
    {
	printf("Could not initialize the required libraries!\n");
	return -1;
    }

    if (!loadMedia())
    {
	printf("Failed to load all media.\n");
	return -1;
    }

    printf("Successfully initialized\n");
    printf("Starting main loop...\n");

    mainLoop();

    close();

    return 0;
}

