#include "SFMLRenderer.hpp"

SFMLRenderer::SFMLRenderer() {}

SFMLRenderer ::~SFMLRenderer()
{
    this->_window->close();
    if (this->_window)
        delete this->_window;
}

void SFMLRenderer::init(int width, int height, int cellSize)
{
    this->_width = width;
    this->_height = height;
    this->_cellSize = cellSize;

    this->_window = new sf::RenderWindow(
        sf::VideoMode(width * cellSize, height * cellSize),
        "nibbler");
}

void SFMLRenderer::setCellColour(int x, int y, Colour colour)
{
    sf::RectangleShape shape(sf::Vector2f(this->_cellSize, this->_cellSize));
    const auto [r, g, b] = colour;

    shape.setFillColor(sf::Color(r, g, b, 0xff));
    shape.setPosition(x * this->_cellSize, y * this->_cellSize);

    this->_window->draw(shape);
}

void SFMLRenderer::getEvents(EventQueue &events)
{
    sf::Event e;

    while (this->_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            events.push(eEventType::quit);
        else if (e.type == sf::Event::KeyPressed)
            switch (e.key.code)
            {
            case sf::Keyboard::Up:
                events.push(eEventType::up);
                break;
            case sf::Keyboard::Left:
                events.push(eEventType::left);
                break;
            case sf::Keyboard::Down:
                events.push(eEventType::down);
                break;
            case sf::Keyboard::Right:
                events.push(eEventType::right);
                break;
            case sf::Keyboard::Escape:
                events.push(eEventType::esc);
                break;
            default:
                break;
            }
    }
}

void SFMLRenderer::blit()
{
    this->_window->display();
    this->_window->clear();
}

extern "C" IRenderer *getRendererInstance(void)
{
    return new SFMLRenderer();
}