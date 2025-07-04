#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class EventHandler
{

public:
	EventHandler() = default;
	~EventHandler() = default;
	static void HandleInputEvents(RenderWindow& window);

private:
	static Event event;
};