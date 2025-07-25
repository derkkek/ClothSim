#include "Application.h"
Application::Application(float width, float height)
    :width(width), height(height),
    renderer(new Renderer), window(sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height) }), "Cloth Simulation")),
    deltaClock(), editor(new Editor(window))
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

    scene = new Cloth(50.0f, 1870.0f, 50.0f, 580.0f, 10.0f);
}

void Application::Update()
{

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();

        window.clear();

        EventHandler::HandleInputEvents(window);
        editor->HandleEvents(window, EventHandler::event);

        InteractSceneByEditor();//encapsulate this into scene


        scene->InteractByInput();
        scene->Update(dt, editor->editorConstraintsIterationCount);

        //renderer->DrawGeometry(cloth->Particles(), cloth->Lines(), window);
        renderer->DrawLines(scene->Lines(), window);

        editor->DrawUI(window, deltaClock);

        window.display();
    }
}
void Application::Terminate()
{

    delete scene;
    scene = nullptr;

    delete renderer;
    renderer = nullptr;

    editor->Terminate();
    delete editor;
    editor = nullptr;

}

void Application::InteractSceneByEditor()
{

    scene->SetGravity(editor->editorGravity);

}
