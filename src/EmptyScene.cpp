#include "EmptyScene.h"
#include <iostream>
#include <set>
#include <algorithm>

EmptyScene::EmptyScene()
	: lineDrawingState(IDLE), lineStartingParticle(nullptr), temporaryLine(nullptr), prevMouseLeftPressed(false), prevMouseRightPressed(false)
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
			AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f));
		}

	}
	else if (state == Editor::State::RUN) // feels off this shouldn't be in here..
	{
		if (temporaryLine != nullptr)
		{
			DeleteTemporaryLine();
		}
		
		static Particle* grabbedParticle = nullptr;

		if (eventHandler.mouseLeftPressed)
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
			if(grabbedParticle)
			grabbedParticle->SetPosition(EventHandler::mouseWorld.x, EventHandler::mouseWorld.y, 0.0f);

		}
		else if(grabbedParticle)
		{
			grabbedParticle->selected = false;
			grabbedParticle = nullptr;
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
					line->Update();
				}
			}
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

void EmptyScene::ConstructUniqueLines()
{
	std::set<std::pair<Particle*, Particle*>> existingLines;
	for (Particle* particle : particles)
	{
		for (Particle* other : particles)
		{
			if (other != particle)
			{
				auto linePair = std::minmax(particle, other);
				if (existingLines.find(linePair) == existingLines.end()) //if the unique pair doesn't exists in our set. 
				{
					float distance = Arithmetic::GetDistance(particle, other);
					if (distance < 500.0f)
					{
						lines.push_back(new Line(particle, other, distance));
						existingLines.insert(linePair);
					}

				}
			}

		}

	}
	existingLines.clear();

	//lines.push_back(new Line(particles.back(), particles.at(particles.size() - 2), Arithmetic::GetDistance(particles.back(), particles.at(particles.size() - 2))));
}


std::vector<Particle*> EmptyScene::GetNeighbors(Particle* particle)
{
	return particles;
}

void EmptyScene::DrawLines(EventHandler& eventHandler)
{
	sf::Vector3f mousePos = sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f);

	if (lineDrawingState == IDLE)
	{
		StartDrawingLine(eventHandler);
	}
	else if (lineDrawingState == GRABBING)
	{
		CompleteDrawingLine(eventHandler);
	}

	else if (lineDrawingState == CHAIN)
	{
		ChainLine(eventHandler);
	}
}

void EmptyScene::StartDrawingLine(EventHandler& eventHandler)
{
	if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
	{
		for (Particle* p : particles)
		{
			if (Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld) < 20.0f)
			{
				lineStartingParticle = p;
				temporaryLine = new Line(lineStartingParticle, sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f), 0, true);
				lines.push_back(temporaryLine);
				lineDrawingState = GRABBING;
				break;
			}
		}
	}
}

void EmptyScene::CompleteDrawingLine(EventHandler& eventHandler)
{
	// On mouse press, try to finish the line
	if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
	{
		for (Particle* p : particles)
		{
			if (p != lineStartingParticle && Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld) < 20.0f)
			{
				// Create the actual line
				lines.push_back(new Line(lineStartingParticle, p, Arithmetic::GetDistance(lineStartingParticle, p)));

				// Remove and delete the temporary 
				DeleteTemporaryLine();

				// Reset state
				lineStartingParticle = p;
				temporaryLine = nullptr;
				//chainParticle = p;
				lineDrawingState = CHAIN;
				break;
			}
		}
	}
}

void EmptyScene::ChainLine(EventHandler& eventHandler)
{
	if (temporaryLine == nullptr && lineStartingParticle != nullptr)
	{
		// Create another temporary.
		temporaryLine = new Line(lineStartingParticle, sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f), 0, true);
		lines.push_back(temporaryLine);
	}
	if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
	{
		for (Particle* p : particles)
		{
			if (p != lineStartingParticle && Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld) < 20.0f)
			{
				lines.push_back(new Line(lineStartingParticle, p, Arithmetic::GetDistance(lineStartingParticle, p)));

				DeleteTemporaryLine();

				// Reset state
				lineStartingParticle = p;
				temporaryLine = nullptr;
				lineDrawingState = CHAIN;
				break;
			}
		}
	}
}

void EmptyScene::DeleteTemporaryLine()
{
	auto it = std::find(lines.begin(), lines.end(), temporaryLine);
	if (it != lines.end())
	{
		delete* it;
		lines.erase(it);
	}
}


