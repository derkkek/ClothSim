#include "IScene.h"
#include <iostream>
IScene::IScene()
	:gravity(sf::Vector3f(0.0f, 500.0f, 0.0f)), prevMouseLeftPressed(false), prevMouseRightPressed(false)
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