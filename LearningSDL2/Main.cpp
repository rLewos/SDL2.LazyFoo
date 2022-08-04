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

bool LoadMedia(const char* path);
void close();
LTexture gKeyboardTexture;
LTexture gArraySides[4];


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

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\preview.png");

			bool quit = false;
			SDL_Event e;

			LTexture* currentTexture = nullptr;
			SDL_Rect clip = { 0, 0, xWindow, yWindow };

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				// Key States
				const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
				if (currentKeyStates[SDL_SCANCODE_UP])
				{
					currentTexture = &gArraySides[0];
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					currentTexture = &gArraySides[1];
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					currentTexture = &gArraySides[2];
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					currentTexture = &gArraySides[3];
				}
				else 
				{
					currentTexture = &gKeyboardTexture;
				}


				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				currentTexture->render(gRenderer, 0, 0, &clip);

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

	gKeyboardTexture.loadFromFile(gRenderer, path);

	gArraySides[0].loadFromFile(gRenderer,"F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\up.bmp");
	gArraySides[1].loadFromFile(gRenderer,"F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\down.bmp");
	gArraySides[2].loadFromFile(gRenderer,"F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\left.bmp");
	gArraySides[3].loadFromFile(gRenderer,"F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\right.bmp");
	

	return sucess;
}