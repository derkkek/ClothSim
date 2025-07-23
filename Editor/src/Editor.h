#include <SFML/Graphics.hpp>
#include <memory.h>
#pragma once
using namespace sf;
class Editor
{
public:
	Editor(sf::RenderWindow& window);
	void DrawUI(sf::RenderWindow& window, sf::Clock deltaClock);
	void HandleEvents(RenderWindow& window, Event event);
	void Terminate();
	~Editor() = default;
	
	void Init(sf::RenderWindow& window);

private:
	float width;
	float height;
};

