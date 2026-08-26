#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <sstream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

const char* fontPath = "/usr/share/fonts/OTF/ipamp.ttf";

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font* gFont;

SDL_Texture* gRestartTimerTexture;
int gRestartTimerWidth;
int gRestartTimerHeight;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("Failed to initialize SDL: %s\n", SDL_GetError());
	success = false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
	printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
	success = false;
    }

    if (TTF_Init() < 0)
    {
	printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
	success = false;
    }

    gWindow = SDL_CreateWindow(
	    "HELLO TIMERS :D",
	    SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    SCREEN_WIDTH,
	    SCREEN_HEIGHT,
	    SDL_WINDOW_SHOWN
	    );

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    gFont = TTF_OpenFont(fontPath, 28);

    if (gWindow == nullptr || gRenderer == nullptr || gFont == nullptr)
    {
	printf("Something failed idk.\n");
	success = false;
    }

    return success;
}

void close()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyTexture(gRestartTimerTexture);

    TTF_CloseFont(gFont);

    TTF_Quit();
    IMG_Quit();

    SDL_Quit();
}

bool loadText(const char* text)
{
    SDL_DestroyTexture(gRestartTimerTexture);

    bool success = true;

    SDL_Surface* restartSurface = TTF_RenderText_Solid(gFont, text, SDL_Color{0x00, 0x00, 0x00, 0xFF});
    if (restartSurface == nullptr)
    {
	printf("Error loading text into SDL_Surface: %s\nError:%s\n", text, TTF_GetError());
	success = false;
    }

    SDL_Texture* restartTexture = SDL_CreateTextureFromSurface(gRenderer, restartSurface);
    if (restartTexture == nullptr)
    {
	printf("Error converting SDL_Surface into SDL_Texture: %s\n", SDL_GetError());
	success = false;
    }
    else
    {
	gRestartTimerWidth = restartSurface->w;
	gRestartTimerHeight = restartSurface->h;
    }

    SDL_FreeSurface(restartSurface);
    
    gRestartTimerTexture = restartTexture;

    return success;
}

void timerLoop()
{
    bool quit = false;
    SDL_Event e;

    Uint32 timerStart = 0;
    Uint32 timerDrift = 0;
    Uint32 timerDriftStart = 0;
    Uint32 oldDrift = 0;

    SDL_Rect dest;

    std::stringstream timerText;

    bool updateDrift = false;

    while (quit == false)
    {
	Uint32 tick = SDL_GetTicks();

	while (SDL_PollEvent(&e) != 0)
	{
	    if (e.type == SDL_QUIT)
	    {
		quit = true;
	    }
	    else if (e.type == SDL_KEYDOWN)
	    {
		if (e.key.keysym.sym == SDLK_RETURN)
		{
		    timerStart = tick;
		    timerDrift = 0;
		    timerDriftStart = tick;
		    oldDrift = 0;
		    updateDrift = false;
		}
		else if (e.key.keysym.sym == SDLK_SPACE)
		{
		    updateDrift = !updateDrift;
		    timerDriftStart = tick;
		    if (!updateDrift)
		    {
			oldDrift = timerDrift;
		    }
		}
	    }
	}

	if (updateDrift)
	{
	    timerDrift = tick - timerDriftStart + oldDrift;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	timerText.str("");
	timerText << "Press ENTER to restart the timer.";

	if (!loadText(timerText.str().c_str()))
	{
	    printf("FAILED TO LOAD TEXT IDK\n");
	    return;
	}

	dest = SDL_Rect{SCREEN_WIDTH / 2 - gRestartTimerWidth / 2, 0, gRestartTimerWidth, gRestartTimerHeight}; 
	SDL_RenderCopy(gRenderer, gRestartTimerTexture, nullptr, &dest);

	timerText.str("");
	timerText << "Time: " << tick - timerStart - timerDrift;

	loadText(timerText.str().c_str());

	if (!loadText(timerText.str().c_str()))
	{
	    printf("FAILED TO LOAD TEXT IDK\n");
	    return;
	}
	
	dest = SDL_Rect{SCREEN_WIDTH / 2 - gRestartTimerWidth / 2, SCREEN_HEIGHT / 2 - gRestartTimerHeight / 2, gRestartTimerWidth, gRestartTimerHeight}; 
	SDL_RenderCopy(gRenderer, gRestartTimerTexture, nullptr, &dest);

	SDL_RenderPresent(gRenderer);
    }
}

int main(int argc, char** argv)
{
    if (!init())
    {
	return -1;
    }

    timerLoop();

    close();

    return 0;
}

