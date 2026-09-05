#pragma once

// I COPIED THE CODE OK IM SORRY
// IM TIRED OF WRITING EVERYTHING BY HAND JUST LET ME GET TO THE FUN PART

#include <SDL2/SDL.h> // need this for Uint32 type

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
        Uint32 getTicks();

        // Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        // The clock tick when the timer started
        Uint32 mStartTick;

        // The clock tick when the timer was paused
        Uint32 mPausedTick;

        // The timer status
        bool mPaused;
        bool mStarted;
};

