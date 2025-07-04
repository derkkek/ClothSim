#pragma once
#include "Line.h"
#include "Particle.h"
#include "EventHandler.h"
using namespace sf;
class Cloth
{
public:
	Cloth(float left, float right, float top, float bottom, float step);
	~Cloth() =default;

	void Update(float dt);
	void Render(RenderWindow& window);
	void ParticleGrabber();
	std::vector<Particle*> GetNeighbors(int i, int j);

private:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;

	int rows;
	int cols;

	Vector3f gravity;
	Vector3f wind;

};
