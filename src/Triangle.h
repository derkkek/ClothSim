#pragma once
#include <vector>
#include "Particle.h"
class Triangle
{
public:
	Triangle();
	~Triangle();

private:
	std::vector<Particle*> vertices;
	std::vector<Line*> lines;
};
