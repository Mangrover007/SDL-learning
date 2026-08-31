#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <stdio.h>


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font* gFont;


#include "../include/LPlayer.h"

#include "../include/globals.h"


const char* fontPath = "/usr/share/fonts/OTF/ipam.ttf";
const char* WINDOW_NAME = "HELLO template :D";


Uint8 PLAYER_KEYS[4]
{
    SDL_SCANCODE_W, // move up
    SDL_SCANCODE_S, // move down
    SDL_SCANCODE_A, // move left
    SDL_SCANCODE_D, // move right
};


#include <unordered_map>
std::unordered_map<Uint8, MoveDirection> PK_TO_DIR
{
    {SDL_SCANCODE_W, MoveDirection::UP},
    {SDL_SCANCODE_S, MoveDirection::DOWN},
    {SDL_SCANCODE_A, MoveDirection::LEFT},
    {SDL_SCANCODE_D, MoveDirection::RIGHT},
};


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

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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




void mainLoop()
{
    bool quit = false;
    SDL_Event e;

    LPlayer Player = LPlayer("/home/mango/personal/SDL-learning/SDL/SDL-player/assets/player-sprite.png");

    int keyboardSize;
    const Uint8* keyboardState;

    while (quit == false)
    {
	while (SDL_PollEvent(&e) != 0)
	{
	    if (e.type == SDL_QUIT)
	    {
		quit = true;
	    }
	}

	keyboardState = SDL_GetKeyboardState(&keyboardSize);

	bool isMoving = false;

	for (int key{0}; key < 4; key++)
	{
	    if (keyboardState[PLAYER_KEYS[key]])
	    {
		isMoving = true;
		Player.move(PK_TO_DIR[PLAYER_KEYS[key]]);
	    }
	}

	if (!isMoving)
	{
	    Player.setVelocity(0, 0);
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// write code here
	Player.render();

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

    printf("Successfully initialized\n");
    printf("Starting main loop...\n");

    mainLoop();

    close();

    return 0;
}

