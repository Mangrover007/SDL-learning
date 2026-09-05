#include "../include/LPlayer.h"


void LPlayer::render(Uint8 dt)
{
    mPlayerTexture.render(mPosX, mPosY);
    mHitbox.x = mPosX;
    mHitbox.y = mPosY;
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

    mHitbox = SDL_FRect{
	0, 
	0,
	(float) this->getWidth() + 1,
	(float) this->getHeight() + 1
    };

    mPosX = 0;
    mPosY = 0;
}


void LPlayer::setPos(float x, float y)
{
    mPosX = x;
    mPosY = y;

    mHitbox.x = x;
    mHitbox.y = y;
}


int LPlayer::getHeight()
{
    return mPlayerTexture.getHeight();
}


int LPlayer::getWidth()
{
    return mPlayerTexture.getWidth();
}

bool LPlayer::isColliding(SDL_FRect& hitbox)
{
    float px1 = hitbox.x, px2 = hitbox.x + hitbox.w;
    float py1 = hitbox.y, py2 = hitbox.y + hitbox.h;

    float x1 = mHitbox.x, x2 = mHitbox.x + mHitbox.w;
    float y1 = mHitbox.y, y2 = mHitbox.y + mHitbox.h;

    bool collidingX = false;
    bool collidingY = false;

    if ((px1 <= x2 && x2 <= px2) || (px1 <= x1 && x1 <= px2))
    {
	collidingX = true;
    }

    if ((py1 <= y2 && y2 <= py2) || (py1 <= y1 && y1 <= py2))
    {
	collidingY = true;
    }

    return (collidingX && collidingY);
}

