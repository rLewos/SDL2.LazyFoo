#pragma once
#include <SDL.h>
#include "LButtonSprite.h"

class LButton
{
public:
	LButton();
	~LButton();
	void setPosition(int x, int y);
	void handleEvent(SDL_Event* e);
	void render();

private:
	SDL_Point mPosition;
	LButtonSprite mCurrentSprite;
};

