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

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x,y, mWidth, mHeight };
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
