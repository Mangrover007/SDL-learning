#include "../include/LDot.h"

int scale = 4;

LDot::LDot() : LEntity{"/home/mango/personal/SDL-learning/SDL/SDL-scrolling/assets/player.png"}
{
}

void LDot::render(int camX, int camY)
{
    SDL_Rect destRect = {
	this->getPosX() - camX,
	this->getPosY() - camY,
	this->getWidth() * scale,
	this->getHeight() * scale
    };

    mTexture.render(0, 0, nullptr, &destRect);
}

void LDot::setPos(float x, float y)
{
    mPosX = x;
    mPosY = y;
}

