#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Line.h"
#include "Arithmetic.h"
#include "EventHandler.h"
#include <iostream>
#include "Cloth.h"

int main()
{
    float width = 800;
    float height = 800;
    auto window = sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), "Cloth Simulation");
    window.setFramerateLimit(165);

    sf::Clock clock;

    Cloth cloth(100.0f, 700.0f, 25.0f);

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

