#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "WindowHardware.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

SDL_Texture* LoadMedia(const char* path);
void KeyboardCommands();

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
																								
																								 SDL_Texture* image = LoadMedia("F:\\# Repositorios\\SDL2.LazyFoo\\LearningSDL2\\x64\\Debug\\assets\\texture.png");

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

																																
																								}

																								SDL_DestroyTexture(image);
																								image = nullptr;
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

								SDL_DestroyRenderer(gRenderer);
								SDL_DestroyWindow(gWindow);
								gWindow = nullptr;
								gRenderer = nullptr;

								SDL_Quit();

								return 0;
}


SDL_Texture* LoadMedia(const char* path)
{
								SDL_Surface* image = IMG_Load(path);
								if (image == nullptr)
								{
																std::string error = "Could load surface image: ";
																error.append(IMG_GetError());
																std::cout << error << "\n";

																throw std::exception(error.c_str());
								}

								SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, image);
								if (texture == nullptr)
								{
																std::string error = "Could create texture: ";
																error.append(SDL_GetError());
																std::cout << error << "\n";

																throw std::exception(error.c_str());
								}

								SDL_FreeSurface(image);
								return texture;
}