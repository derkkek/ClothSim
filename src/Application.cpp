#include "Application.h"
Application::Application(float width, float height)
    :width(width), height(height),
    renderer(new Renderer), window(sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(width), static_cast<unsigned int>(height) }), "Cloth Simulation")),
    deltaClock(), dt(0.0f), editor(new Editor(window)), eventHandler()
{
    Init();
}

Application::~Application()
{
    Terminate();
}

void Application::InteractSceneByEditor()
{
    if (editor->gravityChanged)
    {
        scene->SetGravity(editor->editorGravity);
        editor->gravityChanged = false;
    }

    else if (editor->resetButtonClicked)
    {
        IScene* oldScene = scene;
        scene = scene->Recreate();
        delete oldScene;
    }
}

void Application::Init()
{
    window.setFramerateLimit(165);

    clock;{}

    //scene = new Cloth(50.0f, 1870.0f, 50.0f, 580.0f, 10.0f);
    scene = new EmptyScene();
}

void Application::InitFrame()
{
    dt = clock.restart().asSeconds();

    window.clear();
}

void Application::Input()
{
    EventHandler::HandleInputEvents(window);
    editor->HandleStates(window, EventHandler::event);

    /*This feels off...*/
    InteractSceneByEditor();

    if (editor->state == Editor::State::RUN)
    {
        scene->InteractByInput(eventHandler);
    }
}

void Application::Render()
{
    //renderer->DrawGeometry(cloth->Particles(), cloth->Lines(), window);
    //renderer->DrawLines(scene->Lines(), window);
    renderer->DrawGeometry(scene->Particles(), scene->Lines(), window);

    editor->DrawUI(window, deltaClock);

    window.display();
}
void Application::Update()
{
    while (window.isOpen())
    {
        InitFrame();

        Input();

        scene->Update(dt, editor->editorConstraintsIterationCount);
        
        Render();
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



