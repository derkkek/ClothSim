#pragma once
#include "IScene.h"
class EmptyScene : public IScene
{
public:
	EmptyScene();
	~EmptyScene() = default;

	void InteractByInput(EventHandler& eventHandler, Editor::State state) override;
	void Update(float dt, int constraintIteration) override;
	IScene* Recreate() override;
	void ConstructUniqueLines() override;

private:
	std::vector<Particle*> GetNeighbors(Particle* particle);
};