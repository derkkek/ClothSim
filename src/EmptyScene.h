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
	enum LineDrawingState { IDLE, GRABBING, CHAIN };
	LineDrawingState lineDrawingState;
	Particle* lineStartingParticle;
	Particle* grabbedParticle;
	Line* temporaryLine;


	std::vector<Particle*> GetNeighbors(Particle* particle);
	void DrawLines(EventHandler& eventHandler);
	void StartDrawingLine(EventHandler& eventHandler);
	void CompleteDrawingLine(EventHandler& eventHandler);
	void ChainLine(EventHandler& eventHandler);
	void DeleteTemporaryLine();
	void ParticleGrabber();
};