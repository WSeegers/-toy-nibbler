#ifndef _SFMLRenderer_hpp_
#define _SFMLRenderer_hpp_

#include <IRenderer.hpp>
#include <SFML/Graphics.hpp>

class SFMLRenderer : public IRenderer
{
private:
	sf::RenderWindow *_window = 0;

	int _width = -1;
	int _height = -1;
	int _cellSize = -1;

public:
	SFMLRenderer();
	virtual ~SFMLRenderer();

	virtual void init(int width, int height, int cellSize);
	virtual void setCellColour(int width, int height, Colour colour);
	virtual void getEvents(EventQueue &events);

	virtual void blit();
};

extern "C" IRenderer *getRendererInstance(void);

#endif