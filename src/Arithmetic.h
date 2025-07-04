#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
struct Difference
{
	float x;
	float y;
};
class Arithmetic
{

public:
	Arithmetic() = default;
	~Arithmetic() = default;
	static float GetDistance(Particle* p1, Particle* p2);
	static float GetMouseDistance(Particle* p, Vector2f mousePos);
	static float GetLength(Vector2f v);
	static Vector2f GetDifference(Particle* p1, Particle* p2);
private:


};
