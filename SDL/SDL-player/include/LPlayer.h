#include "LTexture.h"
#include "globals.h"

// How do I think the Player class should be like?
//
// I think there should be something that takes all input events
// and feeds it to the correct sub-system. An event delegator.
//
// The event delegator will consume input events and delegate them
// to the correct sub-system.
//
// For example, pressing escape should be delegated to the top-level
// game management sub-system. Pressing movement arrow keys should
// be delegated to the player sub-system.
//
// Inherently, this means I need to check which key was pressed and
// delegate based off of that. The best in that regard is a switch
// statement or an if-elseif-else chain.
//
// For example, if I press W/A/S/D, the player will move in a certain
// direction.


class LPlayer
{
public:
    LPlayer();
    LPlayer(const char* sprite);

    // expose the render method for player texture
    void render(Uint8 dt);

    void setPos(float x, float y);
    float* getPos();

    int getHeight();
    int getWidth();

private:
    LTexture mPlayerTexture;

public:
    float mPosX, mPosY;
};

