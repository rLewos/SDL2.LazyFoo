#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "WindowHardware.h"
#include "LTexture.h"
#include "LButton.h"
#include "LButtonSpriteEnum.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;


const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int BUTTON_TOTAL = 4;

SDL_Rect gSpriteClips[(int) LButtonSpriteEnum::BUTTON_SPRITE_MOUSE_TOTAL];
LTexture gButtonSpriteSheetTexture;
LButton gButtons[BUTTON_TOTAL];

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

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\button.png");

			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					for (int i = 0; i < BUTTON_TOTAL; ++i)
					{
						gButtons[i].handleEvent(&e, BUTTON_WIDTH, BUTTON_HEIGHT);
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gButtons[i].render(gRenderer, &gButtonSpriteSheetTexture, &gSpriteClips[i]);
				}

				SDL_RenderPresent(gRenderer);
			}

			
		}
		else
		{
			
		}
	}
	catch (const std::exception& e)
	{

	}

	close();

	return 0;
}

void close() {

	

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

	gButtonSpriteSheetTexture.loadFromFile(gRenderer, path);
	

	return sucess;
}