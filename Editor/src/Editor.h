#include <SFML/Graphics.hpp>
#include <memory.h>
#pragma once
using namespace sf;

class Editor
{
	friend class Application;

public:
	Editor(sf::RenderWindow& window);
	~Editor() = default;

	void DrawUI(sf::RenderWindow& window, sf::Clock deltaClock);
	void HandleStates(RenderWindow& window, Event event);
	

private:
	enum State
	{
		EDIT, RUN
	};

	State state;
	Vector3f editorGravity;
	int editorConstraintsIterationCount;

	bool editButtonClicked;
	bool runButtonClicked;
	bool resetButtonClicked;

	bool gravityChanged;


	void Init(sf::RenderWindow& window);
	void Terminate();


};

