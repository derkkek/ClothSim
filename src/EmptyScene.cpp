#include "EmptyScene.h"
#include <iostream>
#include <set>
#include <algorithm>

EmptyScene::EmptyScene()
{

}

void EmptyScene::InteractByInput(EventHandler& eventHandler)
{
	static bool prevMouseLeftPressed = false;

	if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
	{
		AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f));

		if (particles.size() > 1)
		{
			ConstructUniqueLines();
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
