#pragma once
#include <SDL.h>

class WindowHardware
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_xWindowSize;
	int m_yWindowSize;

public:
	WindowHardware(int xWindowSize, int yWindowSize);
	~WindowHardware();

	void Init();
};

