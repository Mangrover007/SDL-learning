#include "../include/LPlayer.h"

void LPlayer::move(MoveDirection direction)
{
    if (mIsMoving)
    {
	if (direction == MoveDirection::UP)
	{
	    mVelY = std::max(-20, mVelY - PLAYER_SPEED);
	}

	if (direction == MoveDirection::DOWN)
	{
	    mVelY = std::min(20, mVelY + PLAYER_SPEED);
	}

	if (direction == MoveDirection::LEFT)
	{
	    mVelX = std::max(-20, mVelY - PLAYER_SPEED);
	}

	if (direction == MoveDirection::RIGHT)
	{
	    mVelX = std::min(20, mVelX + PLAYER_SPEED);
	}
    }
}

void LPlayer::render()
{
    if (mIsMoving)
    {
	mPosX += mVelX;
	mPosX = std::min(SCREEN_WIDTH, mPosX);
	mPosX = std::max(0, mPosX);

	mPosY += mVelY;
	mPosY = std::min(SCREEN_HEIGHT, mPosY);
	mPosY = std::max(0, mPosY);
    }
    else
    {
	mVelX = 0;
	mVelY = 0;
    }

    printf("Rendering player at pos: %d %d\n", mPosX, mPosY);
    mPlayerTexture.render(mPosX, mPosY);
}

LPlayer::LPlayer()
{
    mPosX = 0;
    mVelX = 0;

    mPosY = 0;
    mVelY = 0;
}

LPlayer::LPlayer(const char* sprite)
{
    mPlayerTexture = LTexture();
    mPlayerTexture.loadFromFile(sprite);

    mPosX = 0;
    mVelX = 0;

    mPosY = 0;
    mVelY = 0;
}

void LPlayer::setMoving(bool isMoving)
{
    mIsMoving = isMoving;
}

