#pragma once
#include "Line.h"
#include "Particle.h"
#include "EventHandler.h"
#include "IScene.h"
using namespace sf;
class Cloth : public IScene
{
public:
	Cloth(float left, float right, float top, float bottom, float step);
	~Cloth();

	void Update(float dt, int constraintIteration, Editor::State state) override;
	void InteractByInput(EventHandler& eventHandler, Editor::State state) override;
	IScene* Recreate() override;
private:
	
	std::vector<Particle*> grabbedParticles;
	
	void ParticleGrabber() override;
	void DestroyLineByMouse();
	void DestroyLineByOffset();
	void DestroyUnreferencedParticles();

	void ConstructUniqueLines();


	std::vector<Particle*> GetNeighbors(int i, int j);
	int rows;
	int cols;


};
