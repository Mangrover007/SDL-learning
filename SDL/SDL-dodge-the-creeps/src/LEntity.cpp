#include "../include/LEntity.h"


LEntity::LEntity(const char* sprite)
{
    mTexture = LTexture();
    mTexture.loadFromFile(sprite);

    mHitbox = SDL_FRect{
	0, 
	0,
	(float) this->getWidth() + 1,
	(float) this->getHeight() + 1
    };

    mPosX = 0;
    mPosY = 0;
}


int LEntity::getHeight()
{
    return mTexture.getHeight();
}


int LEntity::getWidth()
{
    return mTexture.getWidth();
}


int LEntity::getPosX()
{
    return mPosX;
}


int LEntity::getPosY()
{
    return mPosY;
}


SDL_FRect LEntity::getHitbox()
{
    return mHitbox;
}


bool LEntity::isColliding(const SDL_FRect& hitbox)
{
    // point x1, x2 define the bounds of the projection of the
    // entity on the x axis
    //
    // point y1, y2 define the bounds of the projection of the
    // entity on the y axis
    float px1 = hitbox.x, px2 = hitbox.x + hitbox.w;
    float py1 = hitbox.y, py2 = hitbox.y + hitbox.h;

    // x1, x2 and y1, y2 are bounds of the entity's hitbox that
    // the current entity is being checked against for collision
    float x1 = mHitbox.x, x2 = mHitbox.x + mHitbox.w;
    float y1 = mHitbox.y, y2 = mHitbox.y + mHitbox.h;

    // if the two entities collide on both the x and y projections
    // only then are they truly colliding
    bool collidingX = false;
    bool collidingY = false;

    if ((px1 <= x2 && x2 <= px2) || (px1 <= x1 && x1 <= px2))
    {
	collidingX = true;
    }

    if ((py1 <= y2 && y2 <= py2) || (py1 <= y1 && y1 <= py2))
    {
	collidingY = true;
    }

    return (collidingX && collidingY);
}

