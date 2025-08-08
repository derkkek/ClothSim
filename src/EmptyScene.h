#pragma once
#include "IScene.h"
class EmptyScene : public IScene
{
public:
	EmptyScene();
	~EmptyScene();

	void InteractByInput(EventHandler& eventHandler, Editor::State state) override;
	void Update(float dt, int constraintIteration, Editor::State state) override;
	IScene* Recreate() override;
	void ConstructUniqueLines() override;

private:

	Particle* grabbedParticle;



	std::vector<Particle*> GetNeighbors(Particle* particle);

	void ParticleGrabber() override;
};