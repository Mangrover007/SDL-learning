#pragma once

// Base class inherited by an entity (for now, player and enemy)

#include "LTexture.h"

class LEntity
{
public:
    LEntity(const char* sprite);

    // inheriting class should provide how to render the entity
    virtual void render() = 0;

    int getWidth();
    int getHeight();

    bool isColliding(const SDL_FRect& hitbox);

    int getPosX();
    int getPosY();

    SDL_FRect getHitbox();

protected:
    float mPosX, mPosY;
    SDL_FRect mHitbox;
    LTexture mTexture;
};

