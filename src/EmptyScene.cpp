#include "EmptyScene.h"
#include <iostream>
#include <set>
#include <algorithm>

EmptyScene::EmptyScene()
	: grabbedParticle(nullptr)
{

}

EmptyScene::~EmptyScene()
{
	for (Particle* particle : particles)
	{
		delete particle;
	}
	particles.clear();
	for (Line* line : lines)
	{
		delete line;
	}
	lines.clear();
	lineStartingParticle = nullptr;
	temporaryLine = nullptr;
	lineDrawingState = IDLE;
	prevMouseLeftPressed = false;
	prevMouseRightPressed = false;
}

void EmptyScene::InteractByInput(EventHandler& eventHandler, Editor::State state)
{
	if (state == Editor::State::ADDPARTICLES)
	{
		if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
		{
			AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f), 5.0f);
		}

	}
	else if (state == Editor::State::RUN)
	{
		if (temporaryLine != nullptr)
		{
			DeleteTemporaryLine();
		}
		

		if (eventHandler.mouseLeftPressed)
		{
			ParticleGrabber();
		}

	}

	else if (state == Editor::State::ADDLINES)
	{
		DrawLines(eventHandler);

		if (eventHandler.mouseRightPressed && !prevMouseRightPressed)
		{
			if (temporaryLine != nullptr)
			{
				DeleteTemporaryLine();
				lineDrawingState = IDLE;
				lineStartingParticle = nullptr;
				temporaryLine = nullptr;
			}
			else
			{
				if (!lines.empty())
				{
					Line* lastLine = lines.back();
					delete lastLine;
					lines.pop_back();
				}
				lineDrawingState = IDLE;
				lineStartingParticle = nullptr;
				temporaryLine = nullptr;
			}
		}
		FindAndCreateAllTriangles();
	}

	prevMouseLeftPressed = eventHandler.mouseLeftPressed;
	prevMouseRightPressed = eventHandler.mouseRightPressed;
}

void EmptyScene::Update(float dt, int constraintIteration, Editor::State state)
{
	if (state == Editor::State::RUN)
	{
		for (Particle* particle : particles)
		{
			particle->AddForce(gravity);
			particle->Update(dt);
			particle->ZeroForce();
		}

		for (int i = 0; i < constraintIteration; i++)
		{

			for (Line* line : lines)
			{
				if (!line->temporary)
				{
					line->Update(dt);
				}
			}
		}
		for (Triangle* triangle : triangles)
		{
			triangle->RelaxationUpdate();
		}
	}

	else if (state == Editor::State::ADDLINES)
	{

		for (Line* line : lines)
		{

			if (line->temporary)
			{
				line->UpdateVAO(line->GetP1()->GetPosition(), sf::Vector3f(EventHandler::mouseWorld.x, EventHandler::mouseWorld.y, 0.0f));
			}
		}
	}


}

IScene* EmptyScene::Recreate()
{
	for (Particle* particle : particles)
	{
		delete particle;
	}
	particles.clear();
	for (Line* line : lines)
	{
		delete line;
	}
	lines.clear();
	particles.clear();
	lineStartingParticle = nullptr;
	temporaryLine = nullptr;
	lineDrawingState = IDLE;
	prevMouseLeftPressed = false;
	prevMouseRightPressed = false;
	return new EmptyScene();
}


void EmptyScene::ParticleGrabber()
{
	if (grabbedParticle == nullptr)
	{
		for (Particle* particle : particles)
		{
			float mouseDistance = Arithmetic::GetMouseDistance(particle, EventHandler::mouseWorld);

			if (mouseDistance <= 20.0f)
			{
				grabbedParticle = particle;
				grabbedParticle->selected = true;
				break;
			}
		}
	}
	if (grabbedParticle)
	{
		grabbedParticle->SetPosition(EventHandler::mouseWorld.x, EventHandler::mouseWorld.y, 0.0f);
	}

	else if (grabbedParticle)
	{
			grabbedParticle->selected = false;
			grabbedParticle = nullptr;
	}
}


