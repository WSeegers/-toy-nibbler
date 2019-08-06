#include "./Vec2i.hpp"

Vec2i::Vec2i() {}
Vec2i::Vec2i(int x, int y) : x(x), y(y) {}
Vec2i::Vec2i(const Vec2i &cpy) : x(cpy.x), y(cpy.y) {}

Vec2i &Vec2i::operator=(const Vec2i &rhs)
{
	if (this != &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
	}
	return *this;
}

Vec2i Vec2i::operator+(const Vec2i &rhs)
{
	return Vec2i(this->x + rhs.x,
				 this->y + rhs.y);
}

bool Vec2i::operator==(const Vec2i &rhs)
{
	return (this->x == rhs.x) && (this->y == rhs.y);
}

std::ostream &operator<<(std::ostream &os, const Vec2i &self)
{
	os << '(' << self.x << ',' << self.y << ')';
	return os;
}
