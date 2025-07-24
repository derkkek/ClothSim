#pragma once
#include <vector>
#include "Line.h"
#include "Particle.h"
class IScene
{
public:
	IScene();
	~IScene() = default;

	std::vector<Line*> Lines();
	std::vector<Particle*> Particles();

	virtual void Update(float dt, int constraintIteration) = 0;

	void SetGravity(sf::Vector3f& Gravity);

protected:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;
	sf::Vector3f gravity;


};
