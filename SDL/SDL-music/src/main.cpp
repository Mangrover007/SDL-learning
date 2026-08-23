#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture *gTexture;

bool init()
{
    bool success = true; 

    // initialize SDL system, gWindow, gRenderer
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
	printf("Error initializing SDL: %s\n", SDL_GetError());
	success = false;
    }

    gWindow = SDL_CreateWindow(
	    "HELLO MUSIC :D :D",
	    SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    800,
	    640,
	    SDL_WINDOW_SHOWN
	    );

    if (gWindow == nullptr)
    {
	printf("Error initializing SDL Window: %s\n", SDL_GetError());
	success = false;
    }
    else
    {
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr)
	{
	    printf("Error creating SDL Renderer: %s\n", SDL_GetError());
	    success = false;
	}
    }

    printf("SDL has been initialized\n");

    // Initialize SDL_mixer and open an audio device (saved internally in the library I assume)
    int MIX_INIT_FLAGS = MIX_INIT_MP3;
    if (Mix_Init(MIX_INIT_FLAGS) != MIX_INIT_FLAGS)
    {
	printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
	success = false;
    }

    printf("Mix initialization successful, opening Mix Audio Device\n");

    int freq = 48000; // 48 kHz samples?
    int channels = 2; // stereo audio has 2 channels
    int buffer_size = 2048; // ?
    
    // open default audio device for playback
    if (Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, channels, buffer_size) < 0)
    {
	printf("Error opening audio device: %s\n", Mix_GetError());
	success = false;
    }

    printf("Mix has been initialized\n");

    // Initialize SDL_image subsystem
    int IMG_INIT_FLAGS = IMG_INIT_PNG;
    if (IMG_Init(IMG_INIT_FLAGS) != IMG_INIT_FLAGS)
    {
	printf("Error initializing SDL_image: %s\n", IMG_GetError());
	success = false;
    }

    printf("Img has been initialized\n");
    
    return success;
}

/* ----------------------------------------------------------------------- */

Mix_Music* gMusic;

bool loadMedia()
{
    bool success = true;

    // load music
    const char* path = "./assets/Bad_Apple_USSR_version.mp3";

    gMusic = Mix_LoadMUS(path);

    if (gMusic == nullptr)
    {
	printf("Error loading music %s\nError: %s\n", path, Mix_GetError());
	success = false;
    }

    // load texture
    const char* surface_path = "./assets/ussr-bunny.png";
    SDL_Surface* surface = IMG_Load(surface_path);
    if (surface == nullptr)
    {
	printf("Error loading image %s: %s\n", surface_path, IMG_GetError());
	success = false;
    }
    else
    {
	// assume this just works idk
	gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
    }

    return success;
}

/* ----------------------------------------------------------------------- */

void close()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    Mix_CloseAudio();

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

/* ----------------------------------------------------------------------- */

int main(int argc, char** argv)
{
    if (!init())
    {
	printf("Error initializing the program!\n");
	return -1;
    }

    printf("Initialization complete\n");

    if (!loadMedia())
    {
	printf("Error loading media!\n");
	return -1;
    }

    printf("All media loaded\n");

    int paused = 1;
    Mix_PauseAudio(paused);

    int loop = -1;
    Mix_PlayMusic(gMusic, loop);

    bool quit = false;
    SDL_Event e;
    while (quit == false)
    {
	// process events
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
		    printf("Enter key pressed\n");
		    paused ^= 1;
		    Mix_PauseAudio(paused);
		}
	    }
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

	SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}

