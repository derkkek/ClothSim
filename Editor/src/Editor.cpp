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
    ,gravityChanged(false), resetButtonClicked(false), addParticlesButtonClicked(false), addLinesButtonClicked(false), io(), currentSceneType(1), sceneChanged(false)
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

    // Scene Type Dropdown
    const char* sceneTypes[] = { "Cloth", "Empty Scene" };
    if (ImGui::Combo("Scene Type", &currentSceneType, sceneTypes, IM_ARRAYSIZE(sceneTypes)))
    {
        sceneChanged = true;
    }

    ImGui::Separator(); // Add a visual separator

    editButtonClicked = ImGui::Button("Edit");
    runButtonClicked = ImGui::Button("Run");
    resetButtonClicked = ImGui::Button("Reset");
    addParticlesButtonClicked = ImGui::Button("Add Particles");
    addLinesButtonClicked = ImGui::Button("Add Lines");

    if (state == EDIT)
    {
        ImGui::Text("Current State: Edit");
        if (ImGui::SliderFloat("Gravity", &editorGravity.y, 0.0f, 2000.0f))
        {
            gravityChanged = true;
        }
        ImGui::SliderInt("Constraint Iteration:", &editorConstraintsIterationCount, 1, 30);
    }
    else if (state == RUN)
    {
        ImGui::Text("Current State: Run");
    }
    else if (state == ADDPARTICLES)
    {
        ImGui::Text("Current State: Adding Particles");
        ImGui::Text("Add some particles with your mouse.");
    }
    else if (state == ADDLINES)
    {
        ImGui::Text("Current State: Adding Lines");
        ImGui::Text("Connect Lines with mouse.");
    }

    // Display current scene type
    ImGui::Separator();
    ImGui::Text("Current Scene: %s", sceneTypes[currentSceneType]);

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
    else if (addParticlesButtonClicked)
    {
        state = ADDPARTICLES;
    }
    else if (addLinesButtonClicked)
    {
        state = ADDLINES;
    }
}

bool Editor::MouseIsOnUI()
{
    return io->WantCaptureMouse;
}
