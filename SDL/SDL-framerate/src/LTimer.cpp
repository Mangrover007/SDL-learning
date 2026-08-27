#include "../include/LTimer.h"

LTimer::LTimer()
{
    mStartTick = 0;
    mPausedTick = 0;
    mPaused = false;
    mStarted = false;
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused;
}

void LTimer::start()
{
    if (!mStarted)
    {
	mStarted = true;
	mPaused = false;

	mStartTick = SDL_GetTicks();
	mPausedTick = 0;
    }

    printf("Timer started: %d\n", mStartTick);
}

void LTimer::stop()
{
    if (mStarted)
    {
	mStarted = false;
	mPaused = false;

	mStartTick = 0;
	mPausedTick = 0;
    }
}

void LTimer::pause()
{
    if (mStarted && !mPaused)
    {
	mPaused = true;
	mPausedTick = SDL_GetTicks();
    }
}

void LTimer::unpause()
{
    if (mStarted && mPaused)
    {
	mPaused = false;

	Uint32 resume_tick = SDL_GetTicks();

	Uint32 diff = mPausedTick - mStartTick;
	mStartTick = resume_tick - diff;
    }
}

Uint32 LTimer::getTicks()
{
    if (!mStarted)
    {
	return 0;
    }

    Uint32 ticks = SDL_GetTicks();

    if (mPaused)
    {
	return mPausedTick - mStartTick;
    }

    return ticks - mStartTick;
}

