#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

class LTexture
{
public:
    LTexture();

    void render(int posX, int posY);

    // Load image into a SDL_Texture
    bool loadFromFile(const std::string& path);

    // Load text into a SDL_Texture
    bool loadTTF(const std::string& text, SDL_Color color);

    void free();

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;
    int mHeight;
    int mWidth;
};

