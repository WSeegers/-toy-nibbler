#ifndef _vec2i_hpp_
#define _vec2i_hpp_

#include <utility>

struct Vec2i
{
	int x = 0;
	int y = 0;

	Vec2i();
	Vec2i(int x, int y);
	Vec2i(const Vec2i &cpy);

	Vec2i &operator=(const Vec2i &rhs);

	Vec2i operator+(const Vec2i &rhs);
	bool operator==(const Vec2i &rhs);
};

#endif
