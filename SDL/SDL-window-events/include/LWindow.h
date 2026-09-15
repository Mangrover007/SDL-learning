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

private:
    SDL_Window* mWindow;

    bool mFullscreen;
};

