#ifndef _CellMap_hpp_
#define _CellMap_hpp_

#include "Vec2i.hpp"
#include "IRenderable.hpp"
#include "../include/Colour.hpp"

#include <stdint.h>
#include <vector>
#include <map>

enum eCellType
{
	empty,
	wall,
	food
};

class CellMap : public IRenderable
{
public:
	Colour _colourMap[3] =
			{{0, 0, 0},
			 {0xff, 0xff, 0xff},
			 {0xff, 0xa5, 0}};

private:
	std::vector<eCellType> _map = {};
	uint32_t _width;
	uint32_t _height;

	void assertInBounds(Vec2i pos);

public:
	CellMap(uint32_t width, uint32_t height);
	~CellMap();

	void setCell(Vec2i pos, eCellType cellType);
	eCellType atCell(Vec2i pos);

	virtual void render(IRenderer &renderer) const;
};

#endif
