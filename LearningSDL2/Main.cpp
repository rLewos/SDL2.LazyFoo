#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "WindowHardware.h"
#include "LTexture.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

SDL_Rect gSpriteClips[4];
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

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr) {
				// TODO: ERROR
			}

			// Set SDL_Renderer background color to white.
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\sprites.png");

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

					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_1:
							std::cout << "1" << "\n";
							break;
						case SDLK_UP:
							std::cout << "UP" << "\n";
							break;

						case SDLK_DOWN:
							std::cout << "DOWN" << "\n";
							break;

						case SDLK_RIGHT:
							std::cout << "RIGHT" << "\n";
							break;

						case SDLK_LEFT:
							std::cout << "LEFT" << "\n";
							break;

						default:
							break;
						}
						break;

					default:
						break;
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer , 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gSpriteSheetTexture.render(gRenderer, 0,0, &gSpriteClips[0]);
				gSpriteSheetTexture.render(gRenderer, xWindow - gSpriteClips[1].w, 0, &gSpriteClips[1]);
				gSpriteSheetTexture.render(gRenderer, 0, yWindow - gSpriteClips[2].h, &gSpriteClips[2]);
				gSpriteSheetTexture.render(gRenderer, xWindow - gSpriteClips[3].w, yWindow - gSpriteClips[3].h, &gSpriteClips[3]);

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
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;

	}

	return sucess;
}