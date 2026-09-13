#include "../include/LPlayer.h"

LPlayer::LPlayer(const char* sprite) : LEntity {sprite}
{
}

void LPlayer::setPos(float x, float y)
{
    mPosX = x;
    mPosY = y;

    mHitbox.x = x;
    mHitbox.y = y;
}

void LPlayer::render()
{
    mTexture.render(mPosX, mPosY);
    mHitbox.x = mPosX;
    mHitbox.y = mPosY;
}

