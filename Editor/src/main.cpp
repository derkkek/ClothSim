#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Editor.h"

int main() 
{
    Application app;

    app.Update();

    app.Terminate();

    return 0;
}