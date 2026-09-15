#pragma once

#include <SDL2/SDL.h>
#include "globals.h"

class LWindow
{
public:
    LWindow();
    bool init();
    SDL_Renderer* createRenderer();
    void free();

    void handleEvents(SDL_Event& e);

    void getWindowSize(int* width, int* height);

private:
    SDL_Window* mWindow;

    bool mFullscreen;
};

