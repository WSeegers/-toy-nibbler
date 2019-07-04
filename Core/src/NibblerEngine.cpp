#include "NibblerEngine.hpp"

#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

NibblerEngine::NibblerEngine(const std::string &path)
	: _path(path),
	  _cellMap(50, 50)
{
	this->_cellMap.setCell(Vec2i(10, 10), eCellType::wall);
	this->_cellMap.setCell(Vec2i(10, 11), eCellType::food);
	this->_cellMap.setCell(Vec2i(11, 10), eCellType::food);

	if (!this->loadRenderer())
		return;

	this->_renderer->init(50, 50, 15);
	this->start();
}

NibblerEngine::~NibblerEngine()
{
	if (this->_renderer)
		delete this->_renderer;
	if (this->_libHandle)
		dlclose(this->_libHandle);
}

void NibblerEngine::updateFunc(AMainLoop &self)
{
	this->handleKeys();
	this->update();
	this->render();
}

void NibblerEngine::handleKeys()
{
	this->_renderer->getEvents(this->_events);

	while (!this->_events.empty())
	{
		switch (this->_events.front())
		{
		case eEventType::up:
			this->_snake.up();
			break;
		case eEventType::left:
			this->_snake.left();
			break;
		case eEventType::down:
			this->_snake.down();
			break;
		case eEventType::right:
			this->_snake.right();
			break;
		case eEventType::esc:
		case eEventType::quit:
			this->stop();
			break;
		default:
			break;
		}
		this->_events.pop();
	}
}

void NibblerEngine::update()
{
	eCellType cellType;

	this->_snake.update();

	if (this->_snake.isColliding())
		this->stop();

	cellType = this->_cellMap.atCell(this->_snake.head());

	switch (cellType)
	{
	case eCellType::empty:
		break;
	case eCellType::food:
		this->_snake.grow();
		this->_cellMap.setCell(this->_snake.head(), eCellType::empty);
		break;
	case eCellType::wall:
		this->stop();
	default:
		break;
	}
}

void NibblerEngine::render()
{
	this->_cellMap.render(*this->_renderer);
	this->_snake.render(*this->_renderer);

	this->_renderer->blit();
}

bool NibblerEngine::loadRenderer()
{
	std::string sdlPath = this->_path + AS_DYNLIB("/SDL2Renderer/libSDL2Renderer");
	// std::string sdlPath = this->_path + AS_DYNLIB("/SFMLRenderer/libSFMLRenderer");

	this->_libHandle = dlopen(sdlPath.c_str(), RTLD_LAZY);
	if (!this->_libHandle)
	{
		std::cerr << "Failed to load sdlRenderer" << std::endl;
		std::cerr << dlerror() << std::endl;

		throw std::runtime_error("Failed to load sdlRenderer");
		return false;
	}

	void *funcPtr = dlsym(this->_libHandle, "getRendererInstance");
	if (!funcPtr)
	{
		std::cerr << "Failed to load getRendererInstance" << std::endl;
		std::cerr << dlerror() << std::endl;

		throw std::runtime_error("Failed to load getRendererInstance");
		return false;
	}

	auto getRendererInstance = reinterpret_cast<IRenderer *(*)(void)>(funcPtr);

	this->_renderer = getRendererInstance();
	return true;
}
