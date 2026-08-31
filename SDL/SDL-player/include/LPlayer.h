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

enum class MoveDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class LPlayer
{
public:
    LPlayer();
    LPlayer(const char* sprite);

    // move based on direction: UP DOWN LEFT RIGHT
    void move(MoveDirection direction);

    // expose the render method for player texture
    void render();

    void setVelocity(int velX, int velY);

private:
    LTexture mPlayerTexture;

    int mPosX, mPosY;
    int mVelX, mVelY;

    const int PLAYER_SPEED = 1;
    const int SPEED_CAP = 8;

    // bool mIsMoving;
};

