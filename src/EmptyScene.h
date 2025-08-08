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

private:

	Particle* grabbedParticle;

	void ParticleGrabber() override;
};