#include "EventHandler.h"
#include <iostream>
sf::Vector2f EventHandler::mouseWorld = sf::Vector2f(0.f, 0.f);
bool EventHandler::mouseLeftPressed = false;
bool EventHandler::mouseRightPressed = false;
void EventHandler::HandleInputEvents(RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            EventHandler::mouseLeftPressed = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            EventHandler::mouseLeftPressed = false;
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            EventHandler::mouseRightPressed = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
        {
            EventHandler::mouseRightPressed = false;
        }
    }
    // Always update mouseWorld to current position
    EventHandler::mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
