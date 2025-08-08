#include "IScene.h"
#include <iostream>
IScene::IScene()
	:gravity(sf::Vector3f(0.0f, 500.0f, 0.0f)), prevMouseLeftPressed(false), prevMouseRightPressed(false)
	,lineDrawingState(IDLE), lineStartingParticle(nullptr), temporaryLine(nullptr)
{
}
IScene::~IScene()
{
}
void IScene::SetGravity(sf::Vector3f& gravity)
{
	this->gravity = gravity;
}

std::vector<Line*> IScene::Lines()
{
	return lines;
}

std::vector<Particle*> IScene::Particles()
{
	return particles;
}
void IScene::AddDynamicParticle(sf::Vector3f position, float radius)
{
	this->particles.push_back(new Particle(position, radius, false));
}

void IScene::AddStaticParticle(sf::Vector3f position, float radius)
{
	this->particles.push_back(new Particle(position, radius, true));
}
void IScene::PopulateScene(std::vector<Particle*>& particles, std::vector<Line*>& lines)
{
	for (Particle* p : particles)
	{
		this->particles.push_back(p);
	}
	for (Line* l : lines)
	{
		this->lines.push_back(l);
	}
}
void IScene::DrawLines(EventHandler& eventHandler)
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

void IScene::StartDrawingLine(EventHandler& eventHandler)
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

void IScene::CompleteDrawingLine(EventHandler& eventHandler)
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

void IScene::ChainLine(EventHandler& eventHandler)
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

void IScene::DeleteTemporaryLine()
{
	auto it = std::find(lines.begin(), lines.end(), temporaryLine);
	if (it != lines.end())
	{
		delete* it;
		lines.erase(it);
	}
}