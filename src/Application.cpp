#include "Application.h"
Application::Application(float width, float height)
    :width(width), height(height), 
    window(sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height) }), "Cloth Simulation")),
    renderer(new Renderer)
{
    Init();
}

Application::~Application()
{
    Terminate();
}

void Application::Init()
{
    window.setFramerateLimit(165);

    clock;{}

    cloth = new Cloth(50.0f, 1870.0f, 50.0f, 580.0f, 10.0f);
}

void Application::Update()
{
    while (window.isOpen())
    {
        EventHandler::HandleInputEvents(window);
        const float dt = clock.restart().asSeconds();

        window.clear();

        cloth->Update(dt);
        renderer->DrawGeometry(cloth->Particles(), cloth->Lines(), window);
        window.display();
    }
}
void Application::Terminate()
{
    delete cloth;
    cloth = nullptr;

    delete renderer;
    renderer = nullptr;
}