#include "Editor.h"
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <EventHandler.h>


void Editor::Init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
}

Editor::Editor(sf::RenderWindow& window)
    :editorGravity(Vector3f(0.0f, 500.0f, 0.0f)), editorConstraintsIterationCount(10), state(RUN), editButtonClicked(false), runButtonClicked(false)
{
    Init(window);
}
void Editor::Terminate()
{
    ImGui::SFML::Shutdown();
}

void Editor::DrawUI(sf::RenderWindow& window, sf::Clock deltaClock)
{
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("Editor Panel");
    ImGui::Text("Hello from the Editor library!");
    editButtonClicked = ImGui::Button("Edit");
    runButtonClicked = ImGui::Button("Run");
    if (state == EDIT)
    {
        ImGui::Text("Current State: Edit");
        ImGui::SliderFloat("Gravity", &editorGravity.y, 0.0f, 2000.0f);
        ImGui::SliderInt("Constraint Iteration:", &editorConstraintsIterationCount, 1, 30);
    }
    else
    {
        ImGui::Text("Current State: Run");
    }

    // ... more ImGui widgets ...
    ImGui::End();
    ImGui::SFML::Render(window);
}

void Editor::HandleEvents(RenderWindow& window, Event event)
{
    ImGui::SFML::ProcessEvent(window, EventHandler::event);

    if (editButtonClicked)
    {
        state = EDIT;
        editButtonClicked = false;
    }
    else if (runButtonClicked)
    {
        state = RUN;
        runButtonClicked = false;
    }
}
