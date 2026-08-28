#include "../include/LTimer.h"


std::chrono::steady_clock::time_point ZERO{};

LTimer::LTimer()
{
    mStartTick = ZERO;
    mPausedTick = ZERO;
    mPaused = false;
    mStarted = false;

    mInitTick = std::chrono::steady_clock::now();
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

	mStartTick = std::chrono::steady_clock::now();
	mPausedTick = ZERO;
    }

    std::chrono::duration<long, std::nano> d = mStartTick - ZERO;
    printf("Timer started: %ld\n", d.count());
}

void LTimer::stop()
{
    if (mStarted)
    {
	mStarted = false;
	mPaused = false;

	mStartTick = ZERO;
	mPausedTick = ZERO;
    }
}

void LTimer::pause()
{
    if (mStarted && !mPaused)
    {
	mPaused = true;
	mPausedTick = std::chrono::steady_clock::now();
    }
}

void LTimer::unpause()
{
    if (mStarted && mPaused)
    {
	mPaused = false;

	std::chrono::steady_clock::time_point resume_tick = std::chrono::steady_clock::now();

	std::chrono::duration diff = mPausedTick - mStartTick;
	mStartTick = resume_tick - diff;
    }
}

std::chrono::duration<long, std::nano> LTimer::getTicks()
{
    if (!mStarted)
    {
	return ZERO - ZERO;
    }

    std::chrono::steady_clock::time_point ticks = std::chrono::steady_clock::now();

    if (mPaused)
    {
	return mPausedTick - mStartTick;
    }

    return ticks - mStartTick;
}

