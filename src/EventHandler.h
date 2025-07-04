#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class EventHandler
{

public:
	EventHandler() = default;
	~EventHandler() = default;
	static void HandleInputEvents(RenderWindow& window);
	static Vector2f mouseWorld;
	static bool mousePressed;


private:
	static Event event;
};