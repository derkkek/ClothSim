#pragma once
#include <vector>
#include "Line.h"
#include "Particle.h"
#include "Editor.h"
#include "EventHandler.h"
class IScene
{
public:
	IScene();
	~IScene() = default;

	virtual void InteractByInput(EventHandler& eventHandler, Editor::State state) = 0; 
	virtual void Update(float dt, int constraintIteration, Editor::State state) = 0;
	virtual IScene* Recreate() = 0;
	virtual void ConstructUniqueLines() = 0;

	void AddDynamicParticle(sf::Vector3f position);
	void AddStaticParticle(sf::Vector3f position);
	void SetGravity(sf::Vector3f& Gravity);
	std::vector<Line*> Lines();
	std::vector<Particle*> Particles();

protected:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;
	sf::Vector3f gravity;


};
