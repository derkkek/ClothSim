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
    ,gravityChanged(false), resetButtonClicked(false), buildButtonClicked(false), io()
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
    resetButtonClicked = ImGui::Button("Reset");
    buildButtonClicked = ImGui::Button("Build");

    if (state == EDIT)
    {
        ImGui::Text("Current State: Edit");

        if (ImGui::SliderFloat("Gravity", &editorGravity.y, 0.0f, 2000.0f))
        {
            gravityChanged = true;
        }

        ImGui::SliderInt("Constraint Iteration:", &editorConstraintsIterationCount, 1, 30);
    }
    else if(state == RUN)
    {
        ImGui::Text("Current State: Run");
    }
    
    else if (state == BUILD)
    {
        ImGui::Text("Current State: Edit");
        ImGui::Text("Add some particles with your mouse.");
    }

    // ... more ImGui widgets ...
    ImGui::End();
    ImGui::SFML::Render(window);
}

void Editor::HandleStates(RenderWindow& window, Event event)
{
    ImGui::SFML::ProcessEvent(window, event);
    io = &ImGui::GetIO();

    if (editButtonClicked)
    {
        state = EDIT;
        //editButtonClicked = false;
    }
    else if (runButtonClicked)
    {
        state = RUN;
        //runButtonClicked = false;
    }
    else if (resetButtonClicked)
    {
        state = RUN;
        //resetButtonClicked = false;
    }
    else if (buildButtonClicked)
    {
        state = BUILD;
    }
}

bool Editor::MouseIsOnUI()
{
    return io->WantCaptureMouse;
}
