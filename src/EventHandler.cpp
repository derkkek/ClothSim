#include "EventHandler.h"
#include <iostream>
sf::Vector2f EventHandler::mouseWorld = sf::Vector2f(0.f, 0.f);
float EventHandler::chooseRadius = 20.0f;
bool EventHandler::mouseLeftPressed = false;
bool EventHandler::mouseRightPressed = false;
sf::Event EventHandler::event;

void EventHandler::HandleInputEvents(RenderWindow& window)
{
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
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta > 0) 
            {
                // Scrolled up
                EventHandler::chooseRadius += 5.0f;
            }
            else if (event.mouseWheelScroll.delta < 0) 
            {
                // Scrolled down
                EventHandler::chooseRadius -= 5.0f;
                if (EventHandler::chooseRadius < 10.0f)
                {
                    EventHandler::chooseRadius = 10.0f;
                }
            }
        }
    }
    // Always update mouseWorld to current position
    EventHandler::mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
