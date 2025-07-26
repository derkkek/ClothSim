#pragma once
#include "IScene.h"
class EmptyScene : public IScene
{
public:
	EmptyScene() = default;
	~EmptyScene() = default;

	void InteractByInput(EventHandler& eventHandler) override;
	void Update(float dt, int constraintIteration) override;
	IScene* Recreate() override;
	void ConstructUniqueLines() override;

private:
	std::vector<Particle*> GetNeighbors(Particle* particle);
};