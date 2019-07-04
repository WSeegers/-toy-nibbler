#ifndef _SDLRenderer_hpp_
#define _SDLRenderer_hpp_

#include <IRenderer.hpp>
#include <SDL2/SDL.h>

class BlockRenderer : public IRenderer
{
private:
	SDL_Window *_window{};
	SDL_Surface *_surface{};

	int _width = -1;
	int _height = -1;
	int _cellSize = -1;

public:
	BlockRenderer();
	virtual ~BlockRenderer();

	virtual void init(int width, int height, int cellSize);
	virtual void setCellColour(int width, int height, Colour colour);
	virtual void getEvents(EventQueue &events);

	virtual void blit();
};

extern "C" IRenderer *getRendererInstance(void);

#endif
