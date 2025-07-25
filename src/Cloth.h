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
	~Cloth() =default;

	void Update(float dt, int constraintIteration) override;
	void InteractByInput() override;

private:

	void ParticleGrabber(bool grab); // passing bool to a function is bad practice..
	void DestroyLineByMouse(bool destroy);
	void DestroyLineByOffset();
	void DestroyUnreferencedParticles();

	void ConstructUniqueLines();


	std::vector<Particle*> GetNeighbors(int i, int j);
	int rows;
	int cols;


};
