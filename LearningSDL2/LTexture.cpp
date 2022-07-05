#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(SDL_Renderer* renderer, std::string filePath)
{
	// Remove texture from memory.
	free();

	SDL_Texture* finalTexture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == nullptr)
	{
		printf("Could not load texture on path: %s\nError: %s", filePath.c_str(), IMG_GetError());
	}
	else 
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x0, 0xFF, 0xFF));
		
		finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (finalTexture == nullptr)
		{
			printf("Could not create texture from surface: %s", SDL_GetError());
		}
		else
		{
			mWidth = surface->w;
			mHeight = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	mTexture = finalTexture;
	return mTexture != nullptr;
}

void LTexture::free()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect rect = { x, y, mWidth, mHeight };
	SDL_RenderCopy(renderer, mTexture, nullptr, &rect);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}