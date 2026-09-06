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


#include "../include/LPlayer.h"
#include "../include/LEnemy.h"
#include <chrono>

#include <unordered_set>

#include <random>

std::string baseDIR = "/home/mango/personal/SDL-learning/SDL/SDL-dodge-the-creeps/";

std::default_random_engine engine(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
std::uniform_real_distribution<double> rng(0.0, 1.0);
std::uniform_real_distribution<double> angle_top(0.0, PI);
std::uniform_real_distribution<double> angle_side(-PI / 2, PI / 2);
std::uniform_int_distribution<int> walls(0, 1);

LEnemy* spawnEnemy(float px, float py)
{
    float x, y;
    float angle;

    // randomly select one of the 4 window edges for spawn
    int wall = walls(engine);

    // 0 = top
    // 1 = bottom
    // 2 = left
    // 3 = right
    
    switch (wall)
    {
	case 0:
	    y = 0;
	    x = rng(engine) * SCREEN_WIDTH;
	    break;
	case 1:
	    y = SCREEN_HEIGHT - 32;
	    x = rng(engine) * SCREEN_WIDTH;
	    break;
	case 2:
	    x = 0;
	    y = rng(engine) * SCREEN_HEIGHT;
	case 3:
	    x = SCREEN_WIDTH - 32;
	    y = rng(engine) * SCREEN_HEIGHT;
	    break;
    }

    // calculate enemy line of sight
    // enemy position: x, y
    // player position: px, py
    angle = std::atan(abs(py - y) / abs(px - x));

    if (x > px)
    {
	if (y > py)
	{
	    angle = PI + angle;
	}
	else
	{
	    angle = PI - angle;
	}
    }
    else
    {
	if (y > py)
	{
	    angle = 2 * PI - angle;
	}
	else
	{
	    angle = angle;
	}
    }

    LEnemy* Enemy = new LEnemy(std::string(baseDIR + "assets/enemy.png").c_str(), x, y, angle);

    return Enemy;
}


#include <sstream>

void mainLoop()
{
    bool quit = false;
    SDL_Event e;

    Uint64 lastTime = SDL_GetTicks64();


    int score = 0;
    Uint64 scoreTimer = SDL_GetTicks64();
    std::stringstream scoreText("0");
    LTexture scoreLabel = LTexture();

    scoreLabel.loadTTF(scoreText.str().c_str(), COL_BLACK);


    LPlayer Player = LPlayer(std::string(baseDIR + "assets/player.png").c_str());
    Player.setPos((SCREEN_WIDTH - Player.getWidth()) / 2, (SCREEN_HEIGHT - Player.getHeight()) / 2);
    
    std::unordered_set<LEnemy*> Enemies;
    std::unordered_set<LEntity*> Entities;

    Entities.insert(&Player);

    Uint64 enemyTimer = SDL_GetTicks64();

    int keyboardSize;
    const Uint8* keyboardState;

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
	
	if (startTime - enemyTimer >= 0.5 * 1000)
	{
	    LEnemy* enemy = spawnEnemy(Player.getPosX(), Player.getPosY());
	    Enemies.insert(enemy);
	    Entities.insert(enemy);
	    enemyTimer = startTime;
	}

	if (startTime - scoreTimer >= 1 * 1000)
	{
	    score += 1;
	    scoreText.str("");
	    scoreText << score;
	    scoreLabel.loadTTF(scoreText.str().c_str(), COL_BLACK);
	    scoreTimer = startTime;
	}

	// player movement
	keyboardState = SDL_GetKeyboardState(&keyboardSize);

	float posX = Player.getPosX();
	float posY = Player.getPosY();

	if (keyboardState[SDL_SCANCODE_W])
	{
	    posY -= PLAYER_SPEED * dt;
	    if (posY > SCREEN_HEIGHT - Player.getHeight())
	    {
		posY = SCREEN_HEIGHT - Player.getHeight();
	    }
	    if (posY < 0)
	    {
		posY = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
	    posY += PLAYER_SPEED * dt;
	    if (posY > SCREEN_HEIGHT - Player.getHeight())
	    {
		posY = SCREEN_HEIGHT - Player.getHeight();
	    }
	    if (posY < 0)
	    {
		posY = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
	    posX += PLAYER_SPEED * dt;
	    if (posX > SCREEN_WIDTH - Player.getWidth())
	    {
		posX = SCREEN_WIDTH - Player.getWidth();
	    }
	    if (posX < 0)
	    {
		posX = 0;
	    }
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
	    posX -= PLAYER_SPEED * dt;
	    if (posX > SCREEN_WIDTH - Player.getWidth())
	    {
		posX = SCREEN_WIDTH - Player.getWidth();
	    }
	    if (posX < 0)
	    {
		posX = 0;
	    }
	}

	Player.setPos(posX, posY);

	for (const auto& enemy : Enemies)
	{
	    if (Player.isColliding(enemy->getHitbox()))
	    {
		printf("Player died\n");
		quit = true;
	    }
	}

	// Render all entities
	scoreLabel.render(0, 0);

	for (const auto& entity: Entities)
	{
	    entity->render();
	}

	// -----------------------------------------------------//
	
	SDL_RenderPresent(gRenderer);

	float frameRate = 1.f / 60.f;
	
	if (dt <= frameRate * 1000)
	{
	    SDL_Delay(frameRate * 1000 - dt);
	}

	lastTime = startTime;
    }

    printf("FINAL SCORE: %d\n", score);

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

