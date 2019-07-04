#include "Snake.hpp"

#include <algorithm>

const Vec2i Snake::_up(0, -1);
const Vec2i Snake::_left(-1, 0);
const Vec2i Snake::_down(0, 1);
const Vec2i Snake::_right(1, 0);

Snake::Snake()
		: _body({Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0)}),
			_nextDirection(Snake::_right),
			_direction(Snake::_right) {}

const Body
		&
		Snake::body() const
{
	return this->_body;
}

void Snake::update()
{
	static int frames = 0;
	if (frames++ % this->_moveDelay)
		return;

	Vec2i head = this->_body.back();
	this->_direction = this->_nextDirection;

	if (this->_grow)
	{
		this->_body.push_back(head + this->_direction);
		this->_grow = false;
	}
	else
	{
		std::rotate(
				this->_body.begin(),
				this->_body.begin() + 1,
				this->_body.end());

		this->_body.back() = head + this->_direction;
	}

	if (isColliding() && this->onCollide)
		this->onCollide();
}

bool Snake::isColliding()
{
	Vec2i &head = this->_body.back();

	Vec2i *found = std::find(this->_body.begin(), this->_body.end(), head)
										 .base();

	return !(found == &head);
}

void Snake::grow() { this->_grow = true; }

void Snake::up()
{
	if (this->_direction.x)
		this->_nextDirection = Snake::_up;
}

void Snake::left()
{
	if (this->_direction.y)
		this->_nextDirection = Snake::_left;
}

void Snake::down()
{
	if (this->_direction.x)
		this->_nextDirection = Snake::_down;
}

void Snake::right()
{
	if (this->_direction.y)
		this->_nextDirection = Snake::_right;
}

void Snake::render(IRenderer &renderer) const
{
	for (const auto cell : this->_body)
	{
		renderer.setCellColour(cell.x, cell.y, this->_bodyCol);
	}
	Vec2i head = this->_body.back();
	renderer.setCellColour(head.x, head.y, this->_headCol);
}

Vec2i Snake::head() { return this->_body.back(); }
