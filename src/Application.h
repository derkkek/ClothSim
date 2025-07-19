#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Line.h"
#include "Arithmetic.h"
#include "EventHandler.h"
#include "Renderer.h"
#include <iostream>
#include "Cloth.h"
#include <chrono>
#include <thread>
#include "Editor.h"
using namespace std::chrono_literals;


class Application
{
public:
	Application(float width = 1920.0f, float height = 1080.0f);
	~Application();

	void Init();
	void Update();
	void Terminate();

private:
	Cloth* cloth;

	Renderer* renderer;

	Editor* editor;
	sf::Clock deltaClock;
	sf::RenderWindow window;
	sf::Clock clock;
	float width;
	float height;
};
