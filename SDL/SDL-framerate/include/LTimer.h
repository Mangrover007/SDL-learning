// I COPIED THE CODE OK IM SORRY
// IM TIRED OF WRITING EVERYTHING BY HAND JUST LET ME GET TO THE FUN PART

#include <SDL2/SDL.h> // need this for Uint32 type
#include <chrono>

class LTimer
{
    public:
        // Initializes variables
        LTimer();

        // The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        // Gets the timer's time
        std::chrono::duration<long, std::ratio<1, 1000000000>> getTicks();

        // Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        // The clock tick when the timer started
	std::chrono::steady_clock::time_point mStartTick;

        // The clock tick when the timer was paused
	std::chrono::steady_clock::time_point mPausedTick;

	std::chrono::steady_clock::time_point mInitTick;

        // The timer status
        bool mPaused;
        bool mStarted;
};

