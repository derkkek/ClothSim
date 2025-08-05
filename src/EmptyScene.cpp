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

			//if (particles.size() > 1)
			//{
			//	ConstructUniqueLines();
			//}

		}


	}
	if (state == Editor::State::ADDLINES)
	{
		static bool foundNearParticle = false;
		//static bool aLineHasCreated = false;
		bool grabbing = false;
		Particle* nearestParticle;
		float mouseParticleDistance;
		Line* temporaryLine;
		sf::Vector3f mousePos = sf::Vector3f(eventHandler.mouseWorld.x, eventHandler.mouseWorld.y, 0.0f);

		if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed)
		{
			std::cout << "1.";
			for (Particle* p : particles)
			{
				mouseParticleDistance = Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld);

				//choose nearest particle relative to the mouse pos.
				if (mouseParticleDistance < 20.0f)
				{	
					nearestParticle = p;
					//create a line from that to mouse position
				
					temporaryLine = new Line(nearestParticle, mousePos, mouseParticleDistance, true);
					lines.push_back(temporaryLine);
					
					//aLineHasCreated = true;
					grabbing = true;
					foundNearParticle = true;
					break;
				}
			}
			if (eventHandler.mouseLeftPressed && !prevMouseLeftPressed && grabbing)
			{
				std::cout << "2.";
				for (Particle* p : particles)
				{
					mouseParticleDistance = Arithmetic::GetMouseDistance(p, eventHandler.mouseWorld);
					if (mouseParticleDistance < 20.0f && nearestParticle && grabbing && nearestParticle != p)
					{
						Line* actualLine = new Line(nearestParticle, p, Arithmetic::GetDistance(nearestParticle, p));
						lines.push_back(actualLine);
						grabbing = false;
					}

				}

				//following snippet instantly deletes the temporary line just after being created.

				//for (auto it = lines.begin(); it != lines.end();)
				//{
				//	Line* line = (*it);

				//	if (line == temporaryLine)
				//	{
				//		delete* it;                // Free memory
				//		it = lines.erase(it);      // Remove from vector, get next iterator
				//	}
				//	else
				//	{
				//		++it;
				//	}
				//}
			}
		}


		//after second particle choose create a new line from first to that one
		//add that line to it's geometries' lines.
		//delete the previous line.
	}
	// Update previous state for next frame
	prevMouseLeftPressed = eventHandler.mouseLeftPressed;
	static bool foundNearParticle = false;
	static bool aLineHasCreated = false;
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
