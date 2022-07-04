#include "WindowHardware.h"

WindowHardware::WindowHardware(int xWindowSize, int yWindowSize)
{
	this->m_window = nullptr;
	this->m_renderer = nullptr;
	this->m_xWindowSize = xWindowSize;
	this->m_yWindowSize = yWindowSize;
}

WindowHardware::~WindowHardware()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;
}

void WindowHardware::Init()
{

}
