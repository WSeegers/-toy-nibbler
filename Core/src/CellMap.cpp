#include "CellMap.hpp"

#include <stdexcept>

CellMap::CellMap(uint32_t width, uint32_t height)
	: _map(width * height),
	  _width(width),
	  _height(height)
{
	this->setBoarder();
}

CellMap::~CellMap() {}

void CellMap::setCell(Vec2i pos, eCellType cellType)
{
	this->assertInBounds(pos);

	this->_map[pos.y * _width + pos.x] = cellType;
}

eCellType CellMap::atCell(Vec2i pos)
{
	this->assertInBounds(pos);
	return this->_map[pos.y * _width + pos.x];
}

void CellMap::render(IRenderer &renderer) const
{
	Colour col;
	for (int y = 0; y < this->_height; y++)
		for (int x = 0; x < this->_width; x++)
		{
			col = this->_colourMap[this->_map[y * this->_width + x]];
			renderer.setCellColour(x, y, col);
		}
}

void CellMap::assertInBounds(Vec2i pos)
{
	if (pos.y < 0 || pos.y > this->_height ||
		pos.x < 0 || pos.x > _width)
		throw std::runtime_error("Position out of bounds");
}

void CellMap::setBoarder()
{
	uint x;
	uint y;

	y = 0;
	for (x = 0; x < this->_width; x++)
	{
		this->setCell(Vec2i(x, y), eCellType::wall);
		this->setCell(Vec2i(x, this->_height - 1), eCellType::wall);
	}
	x = 0;
	for (y = 0; y < this->_height; y++)
	{
		this->setCell(Vec2i(x, y), eCellType::wall);
		this->setCell(Vec2i(this->_width - 1, y), eCellType::wall);
	}
}

uint32_t CellMap::width()
{
	return this->_width;
}

uint32_t CellMap::height()
{
	return this->_height;
}
