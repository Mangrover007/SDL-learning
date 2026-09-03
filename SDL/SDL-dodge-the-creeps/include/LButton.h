#pragma once

#include <SDL2/SDL.h>
#include "./LTexture.h"
#include "./globals.h"

// Allows you to set:
// 1. Where to position the button
// 2. Decide what to do when the button is clicked
class LButton
{
public:
    LButton();
    LButton(const std::string& innerText);

    void setPosition(int x, int y);
    
    void handleEvent(SDL_Event* e);

    // need this because mButtonTexture is a private member
    void render();

private:
    SDL_Point mPos;
    LTexture mButtonTexture;
    std::string mInnerText;

public:
    bool isHeld;
};

