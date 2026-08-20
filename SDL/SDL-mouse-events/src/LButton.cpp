#include "../include/LButton.h"

bool isMouseInsideButton(int width, int height, SDL_Point* curPos)
{
    bool inside = true;

    int x, y;
    SDL_GetMouseState(&x, &y);

    if ((x < curPos->x) || (x > curPos->x + width))
    {
	inside = false;
    }

    if ((y < curPos->y) || (y > curPos->y + height))
    {
	inside = false;
    }

    return inside;
}

LButton::LButton()
{
    mPos.x = 0;
    mPos.y = 0;
    mInnerText = "";

    isHeld = false;

    mButtonTexture.loadTTF(mInnerText, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

LButton::LButton(const std::string& innerText)
{
    mPos.x = 0;
    mPos.y = 0;
    mInnerText = innerText;

    isHeld = false;

    mButtonTexture.loadTTF(mInnerText, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void LButton::setPosition(int x, int y)
{
    mPos.x = std::max(0, mPos.x + x);
    mPos.x = std::min(mPos.x, SCREEN_WIDTH - this->mButtonTexture.getWidth());

    mPos.y = std::max(0, mPos.y + y);
    mPos.y = std::min(mPos.y, SCREEN_HEIGHT - this->mButtonTexture.getHeight());
}

void LButton::handleEvent(SDL_Event* e)
{
    if (isMouseInsideButton(this->mButtonTexture.getWidth(), this->mButtonTexture.getHeight(), &this->mPos))
    {
	switch(e->type)
	{
	case SDL_MOUSEBUTTONDOWN:
	    isHeld = true;
	    printf("BUTTON PRESSED\n");
	    break;
	case SDL_MOUSEBUTTONUP:
	    isHeld = false;
	    printf("BUTTON RELEASED\n");
	    break;
	case SDL_MOUSEMOTION:
	    if (isHeld == true)
	    {
		this->setPosition(e->motion.xrel, e->motion.yrel);
	    }
	    break;
	}
    }
    else
    {
	isHeld = false;
    }
}

void LButton::render()
{
    mButtonTexture.render(mPos.x, mPos.y);
}

