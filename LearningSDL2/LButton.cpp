#include "LButton.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e, const int buttonWidth, const int buttonHeight)
{
	if (e -> type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type = SDL_MOUSEBUTTONUP)
	{
		// Get position where cursor is located.
		int x = 0;
		int y = 0;

		SDL_GetMouseState(&x, &y);

		bool isInside = true;

		if (x < mPosition.x)
		{
			isInside = false;
		}
		else if (x > mPosition.x + buttonWidth)
		{
			isInside = false;
		}
		else if (y < mPosition.y)
		{
			isInside = false;
		}
		else if (y > mPosition.y + buttonHeight)
		{
			isInside = false;
		}


		if (!isInside)
		{
			mCurrentSprite = LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e -> type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void LButton::render(SDL_Renderer* renderer, LTexture* texture, SDL_Rect* spritesheet)
{
	texture->render(renderer, mPosition.x, mPosition.y, spritesheet);
}
