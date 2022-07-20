#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(SDL_Renderer* renderer, std::string filePath);
	void free();
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

