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

const int DEAD_ZONE_CONTROLLER = 8000;

SDL_GameController* gGameController = nullptr;

// Old way with Haptic
SDL_Joystick* gJoystick = nullptr;
SDL_Haptic* gHaptic = nullptr;


LTexture gArrow;

int main(int argc, char* argv[])
{
	try
	{
		WindowHardware* window = nullptr;

		int statusCodeInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);
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

			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning : Linear texture filtering not enabled.");
			}

			// Check if there's a joystick connected
			if (SDL_NumJoysticks() < 1)
			{
				printf("Warning: No joystick connected!\n");
			}
			else
			{
				if (!SDL_IsGameController(0))
				{
					printf("Warning: Joystick not compatible with GameController. %s", SDL_GetError());
				}
				else
				{
					gGameController = SDL_GameControllerOpen(0);
					if (!SDL_GameControllerHasRumble(gGameController))
					{
						printf("Warning: Controller doesn't have rumbles. %s", SDL_GetError());
					}
				}

				if (gGameController == nullptr)
				{
					gJoystick = SDL_JoystickOpen(0);
					if (gJoystick == nullptr)
					{
						printf("Warning: Could not load Joystick - %s", SDL_GetError());
					}
					else
					{
						if (!SDL_JoystickIsHaptic(gJoystick))
						{
							printf("Warning: %s", SDL_GetError());
						}
						else
						{
							// Get joystick haptic device
							gHaptic = SDL_HapticOpenFromJoystick(gJoystick);
							if (gHaptic == nullptr)
							{
								printf("Warning: %s", SDL_GetError());
							}
							else
							{
								// Initialize rumble
								if (SDL_HapticRumbleInit(gHaptic) < 0)
								{
									printf("Warning: %s", SDL_GetError());
								}
							}
						}
					}

				}





			}


			// Set SDL_Renderer background color to white.
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\arrow.png");

			bool quit = false;
			SDL_Event e;

			int xDir = 0;
			int yDir = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_JOYBUTTONDOWN)
					{
						if (gGameController != nullptr)
						{
							// Vibrate controller
							if (SDL_GameControllerRumble(gGameController, 0xFFFF * 3 /4, 0xFFFF * 3/4, 500) < 0)
							{
								printf("Warning: %s", SDL_GetError());
							}
						}
					}

					//else if (e.type == SDL_JOYAXISMOTION)
					//{
					//	// Verify which controller is.
					//	if (e.jaxis.which == 0)
					//	{
					//		// X axis motion
					//		if (e.jaxis.axis == 0)
					//		{
					//			if (e.jaxis.value < -DEAD_ZONE_CONTROLLER)
					//			{
					//				xDir = -1;
					//			}
					//			else if (e.jaxis.value > DEAD_ZONE_CONTROLLER)
					//			{
					//				xDir = 1;
					//			}
					//			else
					//			{
					//				xDir = 0;
					//			}
					//		}
					//		// Y axis motion
					//		else if (e.jaxis.axis == 1)
					//		{
					//			if (e.jaxis.value < -DEAD_ZONE_CONTROLLER)
					//			{
					//				yDir = -1;
					//			}
					//			else if (e.jaxis.value > DEAD_ZONE_CONTROLLER)
					//			{
					//				yDir = 1;
					//			}
					//			else
					//			{
					//				yDir = 0;
					//			}
					//		}
					//	}
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

				if (xDir == 0 && yDir == 0)
				{
					joystickAngle = 0;
				}


				gArrow.render(gRenderer, (xWindow - gArrow.getWidth()) / 2, (yWindow - gArrow.getHeight()) / 2, nullptr, joystickAngle);

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

	gArrow.free();

	if (gGameController != nullptr)
	{
		SDL_GameControllerClose(gGameController);
	}

	if (gJoystick != nullptr)
	{
		SDL_JoystickClose(gJoystick);
	}

	if (gHaptic != nullptr)
	{
		SDL_HapticClose(gHaptic);
	}

	gGameController = nullptr;
	gJoystick = nullptr;
	gHaptic = nullptr;



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

	gArrow.loadFromFile(gRenderer, path);

	return sucess;
}