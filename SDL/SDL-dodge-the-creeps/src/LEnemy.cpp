#include "../include/LEnemy.h"

const int speed = 1;

LEnemy::LEnemy(const char* sprite, float x, float y, float angle) : LEntity {sprite}
{
    mPosX = x;
    mPosY = y;
    mMoveAngle = angle;

    printf("Enemy movement angle: %f\n", angle);
}

void LEnemy::render()
{
    mPosX += (speed * std::cos(mMoveAngle));
    mPosY += (speed * std::sin(mMoveAngle));

    mHitbox.x = mPosX;
    mHitbox.y = mPosY;

    mTexture.render(mPosX, mPosY);
}

