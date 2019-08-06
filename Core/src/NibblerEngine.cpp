#include "NibblerEngine.hpp"

#include <cstdlib>
#include <ctime>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>

const char *rendererPaths[2] =
	{AS_DYNLIB("/SDL2Renderer/libSDL2Renderer"),
	 AS_DYNLIB("/SFMLRenderer/libSFMLRenderer")};

NibblerEngine::NibblerEngine(const std::string &path, uint width, uint height)
	: _path(path),
	  _cellMap(width, height)
{
	std::srand(std::time(0));
	this->addFood();

	this->_snake.setPosition(Vec2i(width / 2, height / 2));

	if (!this->loadRenderer(eRenderer::sdl))
		return;

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
		case eEventType::one:
			this->unloadRenderer();
			this->loadRenderer(eRenderer::sdl);
			break;
		case eEventType::two:
			this->unloadRenderer();
			this->loadRenderer(eRenderer::sfml);
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
		this->addFood();
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

void NibblerEngine::unloadRenderer()
{
	if (this->_renderer)
	{
		delete this->_renderer;
		this->_renderer = nullptr;
	}

	if (this->_libHandle)
	{
		dlclose(this->_libHandle);
		this->_libHandle = nullptr;
	}
}

bool NibblerEngine::loadRenderer(eRenderer selectedRenderer)
{
	std::string sdlPath = this->_path + rendererPaths[selectedRenderer];

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
	this->_renderer->init(
		this->_cellMap.width(),
		this->_cellMap.height(),
		this->cellSize);
	return true;
}

void NibblerEngine::addFood()
{
	auto getFood = [=]() -> Vec2i {
		return Vec2i(
			std::rand() % (this->_cellMap.width() - 2) + 1,
			std::rand() % (this->_cellMap.height() - 2) + 1);
	};

	Vec2i foodPos = getFood();

	this->_cellMap.setCell(foodPos, eCellType::food);
}
