#include "EmptyScene.h"
#include <iostream>
#include <set>

void EmptyScene::InteractByInput(EventHandler& eventHandler)
{
	if (eventHandler.mouseLeftPressed)
	{
		AddDynamicParticle(sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f));
		if (particles.size() > 1)
		{
			ConstructUniqueLines();
		}
	}
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
	return nullptr;
}

void EmptyScene::ConstructUniqueLines()
{
	std::set<std::pair<Particle*, Particle*>> existingLines;
	for each(Particle* particle in particles)
	{
		for each(Particle* other  in particles)
		{
			if(other != particle)
			lines.push_back(new Line(particle, other, Arithmetic::GetDistance(particle, other)));
		}

	}
}

std::vector<Particle*> EmptyScene::GetNeighbors(Particle* particle)
{
	return particles;
}
