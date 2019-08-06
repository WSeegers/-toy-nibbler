#include "./SDL2Inverter.hpp"

SDL2Inverter::SDL2Inverter()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		throw "SDL failed to init";
}

SDL2Inverter::~SDL2Inverter()
{
	if (this->_window)
		SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

void SDL2Inverter::init(int width, int height, int cellSize)
{
	this->_width = width;
	this->_height = height;
	this->_cellSize = cellSize;

	this->_window = SDL_CreateWindow("SDL Inverter",
									 10,
									 10,
									 width * cellSize,
									 height * cellSize,
									 SDL_WINDOW_SHOWN);

	if (!this->_window)
		throw "SDL failed to create window";

	this->_surface = SDL_GetWindowSurface(this->_window);
	SDL_FillRect(this->_surface, 0, 0);
}

void SDL2Inverter::setCellColour(int x, int y, Colour colour)
{
	auto [r, g, b] = colour;
	auto _color = SDL_MapRGB(this->_surface->format, 255 - r, 255 - g, 255 - b);

	SDL_Rect rect = {x * this->_cellSize,
					 y * this->_cellSize,
					 this->_cellSize,
					 this->_cellSize};

	SDL_FillRect(this->_surface, &rect, _color);
}

void SDL2Inverter::blit()
{
	SDL_UpdateWindowSurface(this->_window);
	SDL_FillRect(this->_surface, 0, 0xffffffff);
}

#include <iostream>

void SDL2Inverter::getEvents(EventQueue &events)
{
	SDL_Event e;
	eEventType et;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			events.push(eEventType::quit);
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				et = eEventType::down;
				break;
			case SDLK_LEFT:
				et = eEventType::right;
				break;
			case SDLK_DOWN:
				et = eEventType::up;
				break;
			case SDLK_RIGHT:
				et = eEventType::left;
				break;
			case SDLK_ESCAPE:
				et = eEventType::esc;
				break;
			case SDLK_1:
				et = eEventType::one;
				break;
			case SDLK_2:
				et = eEventType::two;
				break;
			case SDLK_3:
				et = eEventType::three;
				break;
			default:
				continue;
			}
			events.push(et);
		}
	}
}

extern "C" IRenderer *getRendererInstance(void)
{
	return new SDL2Inverter();
}
