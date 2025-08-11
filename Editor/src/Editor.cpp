#include "Editor.h"
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <EventHandler.h>

void Editor::Init(sf::RenderWindow& window)
{
    ImGui::SFML::Init(window);

    // Set professional theme colors with transparent background
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Main colors - Light theme with transparent creamy background
    colors[ImGuiCol_Text] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);  // Dark gray text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);  // Disabled text
    colors[ImGuiCol_WindowBg] = ImVec4(0.98f, 0.96f, 0.92f, 0.85f);  // Creamy background - TRANSPARENT
    colors[ImGuiCol_ChildBg] = ImVec4(0.99f, 0.97f, 0.93f, 0.70f);  // Child windows - lighter cream - TRANSPARENT
    colors[ImGuiCol_PopupBg] = ImVec4(0.99f, 0.97f, 0.93f, 0.90f);  // Popups - light cream - TRANSPARENT
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.65f, 0.25f, 0.40f);  // Green borders - TRANSPARENT
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);  // Border shadow
    colors[ImGuiCol_FrameBg] = ImVec4(0.94f, 0.92f, 0.88f, 0.70f);  // Frame backgrounds - cream - TRANSPARENT
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.87f, 0.93f, 0.85f, 0.80f);  // Frame hovered - light green - TRANSPARENT
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.77f, 0.88f, 0.75f, 0.90f);  // Frame active - green - TRANSPARENT
    colors[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.90f, 0.86f, 0.75f);  // Title background - darker cream - TRANSPARENT
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.77f, 0.88f, 0.75f, 0.85f);  // Active title - green - TRANSPARENT
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.87f, 0.85f, 0.81f, 0.60f);  // Collapsed title - TRANSPARENT
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.96f, 0.94f, 0.90f, 0.75f);  // Menu bar - light cream - TRANSPARENT
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.90f, 0.88f, 0.84f, 0.60f);  // Scrollbar background - cream - TRANSPARENT
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);  // Scrollbar grab - TRANSPARENT
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.60f, 0.60f, 0.60f, 0.90f);  // Scrollbar grab hovered - TRANSPARENT
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);  // Scrollbar grab active
    colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 0.70f, 0.25f, 1.00f);  // Checkmark - green
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.70f, 0.30f, 0.80f);  // Slider grab - green - TRANSPARENT
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.65f, 0.25f, 1.00f);  // Slider grab active - green
    colors[ImGuiCol_Button] = ImVec4(0.90f, 0.88f, 0.84f, 0.70f);  // Button - cream - TRANSPARENT
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.75f, 0.90f, 0.75f, 0.85f);  // Button hovered - light green - TRANSPARENT
    colors[ImGuiCol_ButtonActive] = ImVec4(0.65f, 0.85f, 0.65f, 0.95f);  // Button active - green - TRANSPARENT
    colors[ImGuiCol_Header] = ImVec4(0.80f, 0.90f, 0.80f, 0.70f);  // Header - light green - TRANSPARENT
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.88f, 0.75f, 0.85f);  // Header hovered - green - TRANSPARENT
    colors[ImGuiCol_HeaderActive] = ImVec4(0.70f, 0.85f, 0.70f, 0.95f);  // Header active - green - TRANSPARENT
    colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.65f, 0.25f, 0.40f);  // Separator - green - TRANSPARENT
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.70f, 0.30f, 0.60f);  // Separator hovered - green - TRANSPARENT
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.35f, 0.75f, 0.35f, 0.80f);  // Separator active - green - TRANSPARENT
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.25f, 0.65f, 0.25f, 0.20f);  // Resize grip - green - TRANSPARENT
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.70f, 0.30f, 0.50f);  // Resize grip hovered - green - TRANSPARENT
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.75f, 0.35f, 0.75f);  // Resize grip active - green - TRANSPARENT
    colors[ImGuiCol_Tab] = ImVec4(0.85f, 0.92f, 0.85f, 0.70f);  // Tab - light green - TRANSPARENT
    colors[ImGuiCol_TabHovered] = ImVec4(0.75f, 0.88f, 0.75f, 0.85f);  // Tab hovered - green - TRANSPARENT
    colors[ImGuiCol_TabActive] = ImVec4(0.70f, 0.85f, 0.70f, 0.90f);  // Tab active - green - TRANSPARENT
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.90f, 0.90f, 0.90f, 0.60f);  // Tab unfocused - TRANSPARENT
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.85f, 0.88f, 0.85f, 0.70f);  // Tab unfocused active - TRANSPARENT
    colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);  // Plot lines
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);  // Plot lines hovered
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);  // Plot histogram
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);  // Plot histogram hovered
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.75f, 0.90f, 0.75f, 0.40f);  // Text selection - light green - TRANSPARENT
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.70f);  // Drag drop target - TRANSPARENT
    colors[ImGuiCol_NavHighlight] = ImVec4(0.30f, 0.70f, 0.30f, 0.80f);  // Navigation highlight - green - TRANSPARENT
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);  // Nav windowing highlight - TRANSPARENT
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.15f);  // Nav windowing dim - TRANSPARENT
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.25f);  // Modal window dim - TRANSPARENT

    // Style settings
    style.WindowRounding = 0.0f;  // Sharp corners for docked window
    style.ChildRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 3.0f;
    style.WindowBorderSize = 0.0f;  // No border for docked window
    style.ChildBorderSize = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 0.0f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);  // Reduced padding
    style.FramePadding = ImVec2(6.0f, 4.0f);   // Reduced padding
    style.ItemSpacing = ImVec2(6.0f, 4.0f);    // Reduced spacing
    style.ItemInnerSpacing = ImVec2(4.0f, 3.0f); // Reduced spacing
    style.IndentSpacing = 20.0f;
    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 10.0f;

    // Enable alpha blending for transparency
    style.Alpha = 1.0f;  // Global alpha multiplier (keep at 1.0f for individual control)
}

Editor::Editor(sf::RenderWindow& window)
    :editorGravity(Vector3f(0.0f, 500.0f, 0.0f)), stiffness(1.0f), editorConstraintsIterationCount(10), state(RUN), renderState(GEOMETRY), editButtonClicked(false), runButtonClicked(false)
    , gravityChanged(false), resetButtonClicked(false), addParticlesButtonClicked(false), addLinesButtonClicked(false), io(), currentSceneType(1), sceneChanged(false)
    , saveSceneButtonClicked(false), onlyLinesButtonClicked(false), onlyParticlesButtonClicked(false), geometryButtonClicked(false)
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

    // Get window dimensions
    sf::Vector2u windowSize = window.getSize();
    float panelWidth = 300.0f;

    // Set window flags for auto-resizing panel
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_AlwaysAutoResize;

    // Position at top-right, let height auto-resize
    ImGui::SetNextWindowPos(ImVec2(windowSize.x - panelWidth, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, 0), ImGuiCond_Always); // Height = 0 for auto-resize

    if (ImGui::Begin("Physics Editor", nullptr, window_flags))
    {
        // Header section with title styling
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.6f, 0.2f, 1.0f)); // Dark green
        ImGui::SetWindowFontScale(1.05f);
        ImGui::TextWrapped("Physics Simulation Editor");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Scene Configuration Section
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark text
        ImGui::Text("Scene Configuration");
        ImGui::PopStyleColor();

        ImGui::PushItemWidth(-1); // Full width
        const char* sceneTypes[] = { "Cloth Simulation", "Empty Scene" };
        if (ImGui::Combo("##SceneType", &currentSceneType, sceneTypes, IM_ARRAYSIZE(sceneTypes)))
        {
            sceneChanged = true;
        }
        ImGui::PopItemWidth();

        ImGui::Separator();

        // Control Buttons Section
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark text
        ImGui::Text("Simulation Controls");
        ImGui::PopStyleColor();

        // Row 1: Edit and Run buttons
        float buttonWidth = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) * 0.5f;

        // Edit button with special styling
        if (state == EDIT) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        editButtonClicked = ImGui::Button("Edit", ImVec2(buttonWidth, 32));
        if (state == EDIT) {
            ImGui::PopStyleColor(2);
        }

        ImGui::SameLine();

        // Run button with special styling
        if (state == RUN) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        runButtonClicked = ImGui::Button("Run", ImVec2(buttonWidth, 32));
        if (state == RUN) {
            ImGui::PopStyleColor(2);
        }

        // Row 2: Reset button (full width)
        resetButtonClicked = ImGui::Button("Reset Scene", ImVec2(-1, 28));

        // Row 3: Add Particles and Add Lines
        if (state == ADDPARTICLES) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        addParticlesButtonClicked = ImGui::Button("Add Particles", ImVec2(buttonWidth, 28));
        if (state == ADDPARTICLES) {
            ImGui::PopStyleColor(2);
        }

        ImGui::SameLine();

        if (state == ADDLINES) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        addLinesButtonClicked = ImGui::Button("Add Lines", ImVec2(buttonWidth, 28));
        if (state == ADDLINES) {
            ImGui::PopStyleColor(2);
        }

        // Row 4: Save and Load
        saveSceneButtonClicked = ImGui::Button("Save Scene", ImVec2(buttonWidth, 28));
        ImGui::SameLine();
        loadSceneButtonClicked = ImGui::Button("Load Scene", ImVec2(buttonWidth, 28));

        if (renderState == PARTICLES)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        onlyParticlesButtonClicked = ImGui::Button("Render Particles", ImVec2(buttonWidth, 28));
        if (renderState == PARTICLES) {
            ImGui::PopStyleColor(2);
        }

        ImGui::SameLine();

        if (renderState == LINES)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }
        onlyLinesButtonClicked = ImGui::Button("Render Lines", ImVec2(buttonWidth, 28));

        if (renderState == LINES) {
            ImGui::PopStyleColor(2);
        }
        if (renderState == GEOMETRY)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.85f, 0.65f, 0.90f));  // More opaque when active
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.70f, 0.88f, 0.70f, 0.95f));
        }

        geometryButtonClicked = ImGui::Button("Render Whole Geometry", ImVec2(buttonWidth * 2.0f, 28));

        if (renderState == GEOMETRY) {
            ImGui::PopStyleColor(2);
        }

        ImGui::Separator();

        // Physics Parameters Section (only in Edit mode)
        if (state == EDIT)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark text
            ImGui::Text("Physics Parameters");
            ImGui::PopStyleColor();

            // Gravity slider
            ImGui::Text("Gravity Force:");
            ImGui::PushItemWidth(-1);
            if (ImGui::SliderFloat("##Gravity", &editorGravity.y, 0.0f, 2000.0f, "%.1f"))
            {
                gravityChanged = true;
            }
            ImGui::PopItemWidth();

            ImGui::Text("Stiffness:");
            ImGui::PushItemWidth(-1);
            if (stiffnessChanged = ImGui::SliderFloat("##Stiffness", &stiffness, 0.0001f, 1.0f, "%.1f"));
            ImGui::PopItemWidth();

            // Constraint iterations slider
            ImGui::Text("Constraint Iterations:");
            ImGui::PushItemWidth(-1);
            ImGui::SliderInt("##ConstraintIterations", &editorConstraintsIterationCount, 1, 30, "%d");
            ImGui::PopItemWidth();

            ImGui::Separator();
        }

        // Status Section
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark text
        ImGui::Text("Status Information");
        ImGui::PopStyleColor();

        // Current state display
        ImGui::Text("Current Mode:");
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.6f, 0.2f, 1.0f)); // Dark green
        if (state == EDIT)
        {
            ImGui::Text("Edit Mode");
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // Gray
            ImGui::TextWrapped("Adjust physics parameters and scene settings.");
            ImGui::PopStyleColor();
        }
        else if (state == RUN)
        {
            ImGui::Text("Running");
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // Gray
            ImGui::TextWrapped("Simulation is active. Interact with objects using mouse.");
            ImGui::PopStyleColor();
        }
        else if (state == ADDPARTICLES)
        {
            ImGui::Text("Adding Particles");
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // Gray
            ImGui::TextWrapped("Left-click to add particles to the scene.");
            ImGui::PopStyleColor();
        }
        else if (state == ADDLINES)
        {
            ImGui::Text("Adding Lines");
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // Gray
            ImGui::TextWrapped("Left-click particles to connect them. Right-click to cancel.");
            ImGui::PopStyleColor();
        }
        ImGui::PopStyleColor();

        ImGui::Separator();

        // Scene info
        ImGui::Text("Active Scene:");
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.6f, 0.2f, 1.0f)); // Dark green
        ImGui::Text("%s", sceneTypes[currentSceneType]);
        ImGui::PopStyleColor();
    }
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
    }
    else if (runButtonClicked)
    {
        state = RUN;
    }
    else if (resetButtonClicked)
    {
        state = RUN;
    }
    else if (addParticlesButtonClicked)
    {
        state = ADDPARTICLES;
    }
    else if (addLinesButtonClicked)
    {
        state = ADDLINES;
    }
    else if (loadSceneButtonClicked)
    {
        state = EDIT;
    }
    else if (onlyLinesButtonClicked)
    {
        renderState = LINES;
    }
    else if (onlyParticlesButtonClicked)
    {
        renderState = PARTICLES;
    }
    else if (geometryButtonClicked)
    {
        renderState = GEOMETRY;
    }
}

bool Editor::MouseIsOnUI()
{
    return io->WantCaptureMouse;
}

float Editor::GetStiffness()
{
    return stiffness;
}
