#ifndef _NibblerEngine_hpp_
#define _NibblerEngine_hpp_

#include "AMainLoop.hpp"
#include "Snake.hpp"
#include "../interface/IRenderer.hpp"
#include "CellMap.hpp"

#include <string>

#if __APPLE__
#define _LIBSUFFIX_ "dylib"
#else
#define _LIBSUFFIX_ "so"
#endif

#define AS_DYNLIB(name) name "." _LIBSUFFIX_

class NibblerEngine : private AMainLoop
{
private:
	std::string _path;
	Snake _snake;
	CellMap _cellMap;
	void *_libHandle = 0;
	IRenderer *_renderer = 0;
	std::queue<eEventType> _events;

	virtual void updateFunc(AMainLoop &self);

	void handleKeys();
	void update();
	void render();

	bool loadRenderer();

public:
	NibblerEngine(const std::string &path);
	~NibblerEngine();
};

#endif
