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

    gFont = TTF_OpenFont(fontPath, 56);

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


#include "../include/LTexture.h"
#include "../include/LDot.h"

void mainLoop()
{
    bool quit = false;
    SDL_Event e;

    Uint64 lastTime = SDL_GetTicks64();

    int keyboardSize;
    const Uint8* keyboardState;

    float frameRate = 1.f / 60.f;

    LTexture background = LTexture();
    background.loadFromFile("/home/mango/personal/SDL-learning/SDL/SDL-scrolling/assets/cute-pokemon.png");

    LDot player = LDot{};

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    const int LEVEL_WIDTH = background.getWidth();
    const int LEVEL_HEIGHT = background.getHeight();

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

	// write code here
	
	// updating stuff
	// player movement
	keyboardState = SDL_GetKeyboardState(&keyboardSize);

	float posX = player.getPosX();
	float posY = player.getPosY();

	if (keyboardState[SDL_SCANCODE_W])
	{
	    posY -= PLAYER_SPEED * dt;
	    if (posY > LEVEL_HEIGHT - player.getHeight())
	    {
		posY = LEVEL_HEIGHT - player.getHeight();
	    }
	    if (posY < 0)
	    {
		posY = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
	    posY += PLAYER_SPEED * dt;
	    if (posY > LEVEL_HEIGHT - player.getHeight())
	    {
		posY = LEVEL_HEIGHT - player.getHeight();
	    }
	    if (posY < 0)
	    {
		posY = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
	    posX += PLAYER_SPEED * dt;
	    if (posX > LEVEL_WIDTH - player.getWidth())
	    {
		posX = LEVEL_WIDTH - player.getWidth();
	    }
	    if (posX < 0)
	    {
		posX = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
	    posX -= PLAYER_SPEED * dt;
	    if (posX > LEVEL_WIDTH - player.getWidth())
	    {
		posX = LEVEL_WIDTH - player.getWidth();
	    }
	    if (posX < 0)
	    {
		posX = 0;
	    }
	}

	player.setPos(posX, posY);

	camera.x = posX - (camera.w) / 2;
	camera.y = posY - (camera.h) / 2;

	if (camera.x < 0)
	{
	    camera.x = 0;
	}
	if (camera.x + camera.w > LEVEL_WIDTH)
	{
	    camera.x = LEVEL_WIDTH - camera.w;
	}

	if (camera.y < 0)
	{
	    camera.y = 0;
	}
	if (camera.y + camera.h > LEVEL_HEIGHT)
	{
	    camera.y = LEVEL_HEIGHT - camera.h;
	}

	// rendering stuff
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// background.render((SCREEN_WIDTH - background.getWidth()) / 2, (SCREEN_HEIGHT - background.getHeight()) / 2, &camera);
	background.render(0, 0, &camera);
	player.render(camera.x, camera.y);

	// -----------------------------------------------------//
	
	SDL_RenderPresent(gRenderer);
	
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

