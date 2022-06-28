#include "WindowHardware.h"

WindowHardware::WindowHardware(int xWindowSize, int yWindowSize)
{
								this->window = nullptr;
								this->renderer = nullptr;
								this->xWindowSize = xWindowSize;
								this->yWindowSize = yWindowSize;
}

WindowHardware::~WindowHardware()
{

}

void WindowHardware::Init()
{

}
