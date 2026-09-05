#include "../include/LPlayer.h"


void LPlayer::render(Uint8 dt)
{
    mPlayerTexture.render(mPosX, mPosY);
}


LPlayer::LPlayer()
{
    mPosX = 0;
    mPosY = 0;
}


LPlayer::LPlayer(const char* sprite)
{
    mPlayerTexture = LTexture();
    mPlayerTexture.loadFromFile(sprite);

    mPosX = 0;
    mPosY = 0;
}


void LPlayer::setPos(float x, float y)
{
    mPosX = x;
    mPosY = y;
}


int LPlayer::getHeight()
{
    return mPlayerTexture.getHeight();
}


int LPlayer::getWidth()
{
    return mPlayerTexture.getWidth();
}


