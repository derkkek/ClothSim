#include "Editor.h"
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

void Editor::Init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);
}

void Editor::DrawUI()
{
    ImGui::Begin("Editor Panel");
    ImGui::Text("Hello from the Editor library!");
    // ... more ImGui widgets ...
    ImGui::End();
}
