#ifndef _IRenderable_HPP_
#define _IRenderable_HPP_

#include "../interface/IRenderer.hpp"

class IRenderable
{
public:
	virtual void render(IRenderer &renderer) const = 0;
};

#endif
