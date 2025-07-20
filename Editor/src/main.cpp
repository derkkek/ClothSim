
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Editor.h"

int main() 
{
    Application app;
    Editor editor;
    editor.Init(app.window);
    editor.DrawUI();
    //ImGui::Begin("Editor Window");
    //ImGui::Text("Hello from your Editor executable!");
    //ImGui::End();



    //ImGui::SFML::Update(app.window, app.deltaClock.restart());

    //ImGui::SFML::Render(app.window);
    //app.Update();
    //
    //app.Terminate();
    //ImGui::SFML::Shutdown();

    return 0;
}