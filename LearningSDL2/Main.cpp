#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "WindowHardware.h"
#include "LTexture.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;

LTexture gTextureFont;

bool LoadMedia(const char* path);
void close();

int main(int argc, char* argv[])
{
	try
	{
		WindowHardware* window = nullptr;

		int statusCodeInit = SDL_Init(SDL_INIT_VIDEO);
		int statusCodeTTFInit = TTF_Init();
		
		if (statusCodeTTFInit == -1)
		{
			printf("Could not initialize TTF: %s", TTF_GetError());
		}


		if (statusCodeInit == 0)
		{
			int xWindow = 1024;
			int yWindow = 768;

			gWindow = SDL_CreateWindow("SDL2 Hardware Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xWindow, yWindow, SDL_WINDOW_SHOWN);
			if (gWindow == nullptr) {
				// TODO: ERROR
			}

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr) {
				// TODO: ERROR
			}

			// Set SDL_Renderer background color to white.
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\fonts\\lazy.ttf");

			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gTextureFont.render(gRenderer, (xWindow - gTextureFont.getWidth()) / 2, (yWindow - gTextureFont.getHeight()) / 2);

				SDL_RenderPresent(gRenderer);
			}

			
		}
		else
		{
			/*const char* error = "Could not initialize SDL2" + SDL_GetError();
			std::cout << error << "\n";

			throw std::exception(error);*/
		}
	}
	catch (const std::exception& e)
	{

	}

	close();

	return 0;
}

void close() {

	gTextureFont.free();

	TTF_CloseFont(gFont);
	gFont = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


bool LoadMedia(const char* path)
{
	bool sucess = true;

	gFont = TTF_OpenFont(path, 28);
	if (gFont == nullptr)
	{
		printf("Could not load font: %s", TTF_GetError());
	}
	else
	{
		SDL_Color color = {0,0,0};
		if (!gTextureFont.loadFromRenderedFont(gRenderer, gFont, "The quick brown fox jumps over the lazy dog", color))
		{
			printf("Could not load texture: %s", SDL_GetError());
		}
	}
	

	return sucess;
}