#include "EmptyScene.h"
#include <iostream>
#include <set>
#include <algorithm>

EmptyScene::EmptyScene()
{

}

void EmptyScene::InteractByInput(EventHandler& eventHandler, Editor::State state)
{
	static bool prevMouseLeftPressed = false;
	static enum { IDLE, GRABBING } lineState = IDLE;
	static Particle* startingParticle = nullptr;
	static Line* temporaryLine = nullptr;

	if (state == Editor::State::ADDPARTICLES)
	{
		if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
		{
			AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f));
		}
	}

	if (state == Editor::State::ADDLINES)
	{
		sf::Vector3f mousePos = sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f);

		if (lineState == IDLE)
		{
			if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
			{
				for (Particle* p : particles)
				{
					if (Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld) < 20.0f)
					{
						startingParticle = p;
						temporaryLine = new Line(startingParticle, mousePos, 0, true);
						lines.push_back(temporaryLine);
						lineState = GRABBING;
						break;
					}
				}
			}
		}
		else if (lineState == GRABBING)
		{
			// On mouse press, try to finish the line
			if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
			{
				for (Particle* p : particles)
				{
					if (p != startingParticle && Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld) < 20.0f)
					{
						// Create the actual line
						lines.push_back(new Line(startingParticle, p, Arithmetic::GetDistance(startingParticle, p)));
						// Remove and delete the temporary line
						auto it = std::find(lines.begin(), lines.end(), temporaryLine);
						if (it != lines.end())
						{
							delete* it;
							lines.erase(it);
						}
						// Reset state
						startingParticle = nullptr;
						temporaryLine = nullptr;
						lineState = IDLE;
						break;
					}
				}
			}
		}
	}

	prevMouseLeftPressed = eventHandler.mouseLeftPressed;
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
	lines.clear();
	particles.clear();
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
