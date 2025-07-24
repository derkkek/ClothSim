#include "IScene.h"
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