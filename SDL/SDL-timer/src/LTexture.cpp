#include "../include/LTexture.h"

LTexture::LTexture()
{
    mHeight = 0;
    mWidth = 0;
    mTexture = nullptr;
}

bool LTexture::loadFromFile(const std::string& path)
{
    free();

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
	printf("Failed to load %s\nError:%s\n", path.c_str(), IMG_GetError());
	return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (texture == nullptr)
    {
	printf("Failed to convert surface to texture: %s\nError: %s\n", path.c_str(), SDL_GetError());
	return false;
    }

    mHeight = surface->h;
    mWidth = surface->w;

    SDL_FreeSurface(surface);

    return true;
}

void LTexture::render(int posX, int posY)
{
    SDL_Rect imageRect = {posX, posY, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, nullptr, &imageRect);
}

void LTexture::free()
{
    SDL_DestroyTexture(mTexture);
    mWidth = 0;
    mHeight = 0;
    mTexture = nullptr;
}

bool LTexture::loadTTF(const std::string& text, SDL_Color color)
{
    free();

    SDL_Surface* newText = TTF_RenderUTF8_Solid(gFont, text.c_str(), color);
    // SDL_Surface* newText = IMG_Load("/home/mango/Wallpapers/genshin.jpg");
    
    if (newText == nullptr)
    {
	printf("Error creating \"%s\" into text surface: %s\n", text.c_str(), TTF_GetError());
	return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, newText);

    if (texture == nullptr)
    {
	printf("Error creating texture from text surface: %s\nError: %s\n", text.c_str(), SDL_GetError());
	return false;
    }

    mWidth = newText->w;
    mHeight = newText->h;

    SDL_FreeSurface(newText);
    
    mTexture = texture;

    return true;
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

