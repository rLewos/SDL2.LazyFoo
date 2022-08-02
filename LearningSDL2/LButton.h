#pragma once
#include <SDL.h>
#include "LButtonSpriteEnum.h"

class LButton
{
public:
	LButton();
	~LButton();
	void setPosition(int x, int y);
	void handleEvent(SDL_Event* e, const int buttonWidth, const int buttonHeight);
	void render();

private:
	SDL_Point mPosition;
	LButtonSpriteEnum mCurrentSprite;
};

