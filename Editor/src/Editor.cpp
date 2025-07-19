#include "Editor.h"
#include <iostream>
#include <imgui.h>

void Editor::DrawUI()
{
    ImGui::Begin("Editor Panel");
    ImGui::Text("Hello from the Editor library!");
    // ... more ImGui widgets ...
    ImGui::End();
}
