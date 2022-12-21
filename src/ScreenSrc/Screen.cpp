#include "ScreenManager/Screen.h"

void Screen::run(sf::RenderWindow& window)
{
    for (auto event = sf::Event{}; window.pollEvent(event); )
    {
        switch (event.type)
        {
        case sf::Event::Closed: // Closed game.
            exit(EXIT_SUCCESS);
            break;

        case sf::Event::KeyPressed: // Pressed a key in the keyboard.
            if (event.key.code == sf::Keyboard::Escape) // Exit.
                exit(EXIT_SUCCESS);
            break;

        case sf::Event::MouseButtonReleased: // Clicked on the menu.
            this->handleMouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), window);
            break;

        case sf::Event::MouseMoved: // Moved the mouse on the menu.
        {
            auto mouse_loc = sf::Vector2f(sf::Mouse::getPosition(window)); // Current position of the mouse.
            this->handleHover(mouse_loc);
            break;
        }

        default:
            break;
        }
    }
}

void Screen::setBG(const int index)
{
    this->m_bg.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
    this->m_bg.setTexture(Resources::instance().getBackground(index));
}
