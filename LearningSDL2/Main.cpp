#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "WindowHardware.h"
#include "LTexture.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

LTexture gModuledTexture;
LTexture gBackgroundTexture;


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

			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\fadeout.png");

			bool quit = false;
			SDL_Event e;

			Uint8 alpha = 255;

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
						case SDLK_w:
							if (alpha + 32 > 255)
							{
								alpha = 255;
							}
							else
							{
								alpha += 32;
							}
							break;

						case SDLK_s:
							if (alpha - 32 < 0)
							{
								alpha = 0;
							}
							else {
								alpha -= 32;
							}
							break;

						default:
							break;
						}
						break;

					default:
						break;
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gBackgroundTexture.render(gRenderer, 0x0, 0x0);
				
				gModuledTexture.setAlpha(alpha);
				gModuledTexture.render(gRenderer, 0x0, 0x0);
				

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

	if (!gModuledTexture.loadFromFile(gRenderer, path))
	{
		printf("Failed to load texture!\n");
		sucess = false;
	}
	else 
	{
		gModuledTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}


	if (!gBackgroundTexture.loadFromFile(gRenderer, "F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\fadein.png"))
	{
		printf("Failed to load texture!\n");
		sucess = false;
	}

	return sucess;
}