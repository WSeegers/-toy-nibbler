#ifndef _Snake_hpp_
#define _Snake_hpp_

#include "Vec2i.hpp"
#include "IUpdateable.hpp"
#include "IRenderable.hpp"
#include "../include/Colour.hpp"

#include <vector>

typedef std::vector<Vec2i> Body;
typedef void (*CollideCallback)(void);

class Snake : public IUpdateable, public IRenderable
{
private:
	static const Vec2i _up;
	static const Vec2i _left;
	static const Vec2i _down;
	static const Vec2i _right;

	Colour _headCol = {0x33, 0xCC, 0x00};
	Colour _bodyCol = {0x66, 0x00, 0xCC};

	bool _grow = false;
	Body _body;
	Vec2i _nextDirection;
	Vec2i _direction;

	int _moveDelay = 10; // Frames per block moved

	CollideCallback onCollide{};

public:
	Snake();

	const Body &body() const;

	virtual void update();
	virtual void render(IRenderer &renderer) const;
	void grow();

	void up();
	void left();
	void down();
	void right();

	Vec2i head();

	bool isColliding();
};

#endif
