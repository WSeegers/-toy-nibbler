#include "./SDL2Renderer.hpp"

SDL2Renderer::SDL2Renderer()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		throw "SDL failed to init";
}

SDL2Renderer::~SDL2Renderer()
{
	if (this->_window)
		SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

void SDL2Renderer::init(int width, int height, int cellSize)
{
	this->_width = width;
	this->_height = height;
	this->_cellSize = cellSize;

	this->_window = SDL_CreateWindow("SDL Tutorial",
									 SDL_WINDOWPOS_UNDEFINED,
									 SDL_WINDOWPOS_UNDEFINED,
									 width * cellSize,
									 height * cellSize,
									 SDL_WINDOW_SHOWN);

	if (!this->_window)
		throw "SDL failed to create window";

	this->_surface = SDL_GetWindowSurface(this->_window);
	SDL_FillRect(this->_surface, 0, 0);
}

void SDL2Renderer::setCellColour(int x, int y, Colour colour)
{
	auto [r, g, b] = colour;
	auto _color = SDL_MapRGB(this->_surface->format, r, g, b);

	SDL_Rect rect = {x * this->_cellSize,
					 y * this->_cellSize,
					 this->_cellSize,
					 this->_cellSize};

	SDL_FillRect(this->_surface, &rect, _color);
}

void SDL2Renderer::blit()
{
	SDL_UpdateWindowSurface(this->_window);
	SDL_FillRect(this->_surface, 0, 0);
}

void SDL2Renderer::getEvents(EventQueue &events)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			events.push(eEventType::quit);
		else if (e.type == SDL_KEYDOWN)
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				events.push(eEventType::up);
				break;
			case SDLK_LEFT:
				events.push(eEventType::left);
				break;
			case SDLK_DOWN:
				events.push(eEventType::down);
				break;
			case SDLK_RIGHT:
				events.push(eEventType::right);
				break;
			case SDLK_ESCAPE:
				events.push(eEventType::esc);
				break;
			default:
				break;
			}
	}
}

extern "C" IRenderer *getRendererInstance(void)
{
	return new SDL2Renderer();
}
