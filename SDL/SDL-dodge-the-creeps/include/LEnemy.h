#pragma once

#include "LEntity.h"

// what should the Enemy do?
//
// I want the Enemy to have an initial position, and a mechanism
// to automatically move it in any direction at any angle

class LEnemy : public LEntity 
{
public:
    LEnemy(const char* sprite, float x, float y, float angle);

    void render() override;

private:
    float mMoveAngle;
};

