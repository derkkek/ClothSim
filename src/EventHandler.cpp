#include "EventHandler.h"
#include <iostream>

void EventHandler::HandleInputEvents(RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            
        }
    }
}
