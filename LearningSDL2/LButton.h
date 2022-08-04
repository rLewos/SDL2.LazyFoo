#pragma once
#include <SDL.h>
#include "LButtonSpriteEnum.h"
#include "LTexture.h"

class LButton
{
public:
	LButton();
	~LButton();
	void setPosition(int x, int y);
	void handleEvent(SDL_Event* e, const int buttonWidth, const int buttonHeight);
	void render(SDL_Renderer* renderer, LTexture* texture, SDL_Rect* spritesheet);

private:
	SDL_Point mPosition;
	LButtonSpriteEnum mCurrentSprite;
};

