#pragma once
#include <SDL.h>

class WindowHardware
{
private:
								SDL_Window* window;
								SDL_Renderer* renderer;
								int xWindowSize;
								int yWindowSize;

public:
								WindowHardware(int xWindowSize, int yWindowSize);
								~WindowHardware();

								void Init();
};

