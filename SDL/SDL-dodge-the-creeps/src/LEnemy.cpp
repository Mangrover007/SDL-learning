#include "../include/LEnemy.h"

const int speed = 2;

LEnemy::LEnemy(const char* sprite, float x, float y, float angle) : LEntity {sprite}
{
    mPosX = x;
    mPosY = y;
    mMoveAngle = angle;
}

void LEnemy::render()
{
    mPosX += (speed * std::cos(mMoveAngle));
    mPosY += (speed * std::sin(mMoveAngle));

    mHitbox.x = mPosX;
    mHitbox.y = mPosY;

    mTexture.render(mPosX, mPosY);
}

