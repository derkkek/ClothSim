#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Line.h"
#include "Arithmetic.h"
#include "EventHandler.h"
#include <iostream>
#include "Cloth.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;



int main()
{
    float width = 1920;
    float height = 1080;
    auto window = sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), "Cloth Simulation");
    window.setFramerateLimit(165);

    sf::Clock clock;

    Cloth cloth(50.0f, 1870.0f, 50.0f, 515.0f, 20.0f);
    //std::this_thread::sleep_for(0.5s);  // pause for 1 second
    while (window.isOpen())
    {
        EventHandler::HandleInputEvents(window);
        const float dt = clock.restart().asSeconds();

        window.clear();

        cloth.Update(dt);
        cloth.Render(window);

        window.display();
    }

    return 0;
}

