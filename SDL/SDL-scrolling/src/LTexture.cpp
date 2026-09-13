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

    mTexture = texture;

    SDL_FreeSurface(surface);

    return true;
}



void LTexture::render(int posX, int posY, SDL_Rect* srcRect, SDL_Rect* destRect)
{
    SDL_Rect imageRect = {posX, posY, mWidth, mHeight};

    // imagine the destination rectangle as the place where you will finally
    // render your textures.
    //
    // The final area or screen where you draw your textures is always a constant
    // dimension. For example, this program's screen dimensions are 640x800. This
    // will never change.
    //
    // So you can imagine two different work areas. The final work area - the screen
    // and the back area - where you choose what part of the entire thing you want
    // to render to the screen.
    //
    // if destRect is not defined, then just render the sprite at full its full
    // width and height. When this is done, posX and posY are typically set to 0
    // because you want to render the entire sprite (which is why you didn't clip
    // it at all, thus not setting destRect)
    if (destRect == nullptr)
    {
	destRect = &imageRect;
    }

    // srcRect is where SDL copies the texture data from.
    //
    // srcRect tells which x,y to start picking the sprite data from, and what
    // w,h the rectangle will have.
    //
    // With a 200x400 sprite, rendering the src clip from camX, camY at camWidth,
    // camHeight will pick the sprite data equal to the camera clip starting at
    // camX, camY
    //
    // Then, rendering at the same destination dimensions but from 0,0 will render
    // the sprite clip at full camera width and camera height, effectively, the
    // screen.
    //
    // This is why, if the srcRect is defined, then the destination rectangle's
    // width and height should match.
    //
    // Typically, the full width and height of the texture is simple greater than
    // the source rectangle's width and height, which is why we define a clip to
    // begin with
    if (srcRect != nullptr)
    {
	destRect->w = srcRect->w;
	destRect->h = srcRect->h;
    }

    SDL_RenderCopy(gRenderer, mTexture, srcRect, destRect);
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

