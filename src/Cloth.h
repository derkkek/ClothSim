#pragma once
#include "Line.h"
#include "Particle.h"
using namespace sf;
class Cloth
{
public:
	Cloth(float start, float end, float step);
	~Cloth() =default;

	void Update(float dt);
	void Render(RenderWindow& window);
	std::vector<Particle*> GetNeighbors(int i, int j);

private:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;

	int rows;
	int cols;

	Vector3f gravity;

};
