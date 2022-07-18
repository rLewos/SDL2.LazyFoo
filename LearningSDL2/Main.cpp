#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "WindowHardware.h"
#include "LTexture.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

const int WALKING_FRAMES = 4;
SDL_Rect gSpriteClipts[WALKING_FRAMES];
LTexture gSpriteSheetTexture;

bool LoadMedia(const char* path);
void close();

int main(int argc, char* argv[])
{
	try
	{
		WindowHardware* window = nullptr;

		int statusCodeInit = SDL_Init(SDL_INIT_VIDEO);
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

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\foo.png");

			bool quit = false;
			SDL_Event e;
			int frame = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;

					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_q:
								break;
						}
						break;

					default:
						break;
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				SDL_Rect* currentClip = &gSpriteClipts[frame / 4];
				gSpriteSheetTexture.render(gRenderer, (xWindow - currentClip->w) / 2, (yWindow - currentClip->h) / 2, currentClip);

				SDL_RenderPresent(gRenderer);

				++frame;

				if ((frame/ 4 ) >= WALKING_FRAMES)
				{
					frame = 0;
				}
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

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}


bool LoadMedia(const char* path)
{
	bool sucess = true;

	if (!gSpriteSheetTexture.loadFromFile(gRenderer, path))
	{
		printf("Failed to load texture!\n");
		sucess = false;
	}
	else 
	{
		gSpriteClipts[0].x = 0;
		gSpriteClipts[0].y = 0;
		gSpriteClipts[0].w = 64;
		gSpriteClipts[0].h = 205;

		gSpriteClipts[1].x = 64;
		gSpriteClipts[1].y = 0;
		gSpriteClipts[1].w = 64;
		gSpriteClipts[1].h = 205;

		gSpriteClipts[2].x = 128;
		gSpriteClipts[2].y = 0;
		gSpriteClipts[2].w = 64;
		gSpriteClipts[2].h = 205;

		gSpriteClipts[3].x = 192;
		gSpriteClipts[3].y = 0;
		gSpriteClipts[3].w = 64;
		gSpriteClipts[3].h = 205;
	}

	return sucess;
}