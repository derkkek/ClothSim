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

	if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
	{
		if (state == Editor::State::ADDPARTICLES)
		{

			AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f));

			if (particles.size() > 1)
			{
				ConstructUniqueLines();
			}

		}

		if (state == Editor::State::ADDLINES)
		{
			//choose nearest particle relative to the mouse pos.
			//create a line from that to mouse position
			//update it's VAO accordingly to mouse pos
			//render the line in each frame
			//after second particle choose create a new line from first to that one
			//add that line to it's geometries' lines.
			//delete the previous line.
		}
	}

	// Update previous state for next frame
	prevMouseLeftPressed = eventHandler.mouseLeftPressed;
}

void EmptyScene::Update(float dt, int constraintIteration)
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
			line->Update();
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
