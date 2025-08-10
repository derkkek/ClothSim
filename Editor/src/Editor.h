#include <SFML/Graphics.hpp>
#include <memory.h>
#include <imgui.h>
#pragma once
using namespace sf;

class Editor
{

	friend class Application;

public:
	enum State
	{
		EDIT, RUN, ADDPARTICLES, ADDLINES
	};
	enum RenderState
	{
		LINES, PARTICLES, GEOMETRY
	};

	Editor(sf::RenderWindow& window);
	~Editor() = default;

	void DrawUI(sf::RenderWindow& window, sf::Clock deltaClock);
	void HandleStates(RenderWindow& window, Event event);
	bool MouseIsOnUI();
	

private:


	State state;
	RenderState renderState;
	Vector3f editorGravity;
	int editorConstraintsIterationCount;

	bool editButtonClicked;
	bool runButtonClicked;
	bool resetButtonClicked;
	bool addParticlesButtonClicked;
	bool addLinesButtonClicked;
	bool saveSceneButtonClicked;
	bool loadSceneButtonClicked;
	bool onlyLinesButtonClicked;
	bool onlyParticlesButtonClicked;
	bool geometryButtonClicked;
	
	int currentSceneType;    // 0 = Cloth, 1 = Empty Scene
	bool sceneChanged;       // Flag to detect when scene type changes

	ImGuiIO* io;
	bool gravityChanged;


	void Init(sf::RenderWindow& window);
	void Terminate();


};

