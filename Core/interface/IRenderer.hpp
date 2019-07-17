#ifndef _IRenderer_hpp_
#define _IRenderer_hpp_

#include <stdint.h>
#include <queue>

#include "../include/Colour.hpp"

enum eEventType
{
	up,
	left,
	down,
	right,
	esc,
	quit,
	one,
	two,
	three
};
typedef std::queue<eEventType> EventQueue;

class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual void init(int width, int height, int cellSize) = 0;
	virtual void setCellColour(int x, int y, Colour colour) = 0;
	virtual void getEvents(EventQueue &events) = 0;
	virtual void blit() = 0;
};

#endif
