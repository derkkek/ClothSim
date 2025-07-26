#include "IScene.h"
#include <iostream>
IScene::IScene()
	:gravity(sf::Vector3f(0.0f, 500.0f, 0.0f))
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
void IScene::AddDynamicParticle(sf::Vector3f position)
{
	this->particles.push_back(new Particle(position, false));
}

void IScene::AddStaticParticle(sf::Vector3f position)
{
	this->particles.push_back(new Particle(position, true));
}
