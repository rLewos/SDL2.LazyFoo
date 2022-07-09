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
	//void render(SDL_Renderer* renderer, int x, int y);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

