#pragma once
#include <vector>
#include "Line.h"
#include "Particle.h"
#include "Editor.h"
#include "EventHandler.h"
#include <SFML/Graphics.hpp>
class IScene
{
public:
	IScene();
	virtual ~IScene() = 0;

	virtual void InteractByInput(EventHandler& eventHandler, Editor::State state) = 0; 
	virtual void Update(float dt, int constraintIteration, Editor::State state) = 0;
	virtual IScene* Recreate() = 0;

	void AddDynamicParticle(sf::Vector3f position, float radius);
	void AddStaticParticle(sf::Vector3f position, float radius);
	void SetGravity(sf::Vector3f& Gravity);
	std::vector<Line*> Lines();
	std::vector<Particle*> Particles();
	void PopulateScene(std::vector<Particle*>& particles, std::vector<Line*>& lines);


protected:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;
	sf::Vector3f gravity;

	bool prevMouseLeftPressed;
	bool prevMouseRightPressed;

	enum LineDrawingState { IDLE, GRABBING, CHAIN };
	LineDrawingState lineDrawingState;
	Particle* lineStartingParticle;
	Line* temporaryLine;

	void DrawLines(EventHandler& eventHandler);
	void StartDrawingLine(EventHandler& eventHandler);
	void CompleteDrawingLine(EventHandler& eventHandler);
	void ChainLine(EventHandler& eventHandler);
	void DeleteTemporaryLine();
	virtual void ParticleGrabber() = 0;
};
