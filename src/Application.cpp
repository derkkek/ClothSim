#include "Application.h"
#include "Editor.h"
Application::Application(float width, float height)
    :width(width), height(height), 
    window(sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height) }), "Cloth Simulation")),
    renderer(new Renderer), editor(new Editor), deltaClock()
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
        const float dt = clock.restart().asSeconds();

        window.clear();

        EventHandler::HandleInputEvents(window);

        cloth->Update(dt);

        renderer->DrawGeometry(cloth->Particles(), cloth->Lines(), window);

        //editor->DrawUI();

        window.display();
    }
}
void Application::Terminate()
{
    delete cloth;
    cloth = nullptr;

    delete renderer;
    renderer = nullptr;

    delete editor;
    editor = nullptr;

}