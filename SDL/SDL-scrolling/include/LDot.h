#pragma once

#include "LEntity.h"

class LDot : public LEntity
{
public:
    LDot();

    void render(int camX = 0, int camY = 0) override;

    void setPos(float x, float y);
};

