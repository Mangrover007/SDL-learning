#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <stdio.h>


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font* gFont;


#include "../include/globals.h"


const char* fontPath = "/usr/share/fonts/OTF/ipam.ttf";
const char* WINDOW_NAME = "HELLO template :D";


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


void handleEvent(SDL_Event& e)
{
    // write custom events handlers here   
}


#include "../include/LPlayer.h"

void mainLoop()
{
    bool quit = false;
    SDL_Event e;

    Uint64 lastTime = SDL_GetTicks64();

    std::string baseDIR = "/home/mango/personal/SDL-learning/SDL/SDL-dodge-the-creeps/";

    LPlayer Player = LPlayer(std::string(baseDIR + "assets/player.png").c_str());
    LPlayer Enemy = LPlayer(std::string(baseDIR + "assets/enemy.png").c_str());

    Player.mPosX = (SCREEN_WIDTH - Player.getWidth()) / 2;
    Player.mPosY = (SCREEN_HEIGHT - Player.getHeight()) / 2;

    while (quit == false)
    {
	Uint64 startTime = SDL_GetTicks64();
	Uint64 dt = startTime - lastTime;

	// -----------------------------------------------------//
	
	while (SDL_PollEvent(&e) != 0)
	{
	    if (e.type == SDL_QUIT)
	    {
		quit = true;
	    }
	    else
	    {
		handleEvent(e);
	    }
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// write code here

	Player.render(dt);
	Enemy.render(dt);

	// -----------------------------------------------------//
	
	SDL_RenderPresent(gRenderer);

	float frameRate = 1.f / 60.f;
	
	if (dt <= frameRate * 1000)
	{
	    SDL_Delay(frameRate * 1000 - dt);
	}

	lastTime = startTime;
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

    printf("Successfully initialized\n");
    printf("Starting main loop...\n");

    mainLoop();

    close();

    return 0;
}

